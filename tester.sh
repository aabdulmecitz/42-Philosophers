#!/bin/bash

# Renkli çıktılar için tanımlamalar
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Program adı ve test parametreleri
PHILO="./philo"
TEST_DIR="./tests"
LOG_FILE="$TEST_DIR/test_log.txt"
TIMEOUT=10 # Saniye cinsinden maksimum test süresi

# Test klasörünü oluştur
mkdir -p $TEST_DIR
rm -f $TEST_DIR/*.log $LOG_FILE

# Test sonuçları sayacı
total_tests=0
passed_tests=0

# Yardımcı fonksiyonlar
print_separator() {
    echo "================================================================"
}

run_test() {
    local test_name=$1
    local args=$2
    local expected_output=$3
    local validation_func=$4

    ((total_tests++))
    
    echo -e "${YELLOW}Test $total_tests: $test_name${NC}"
    echo "Args: $args"
    
    # Programı zaman aşımı ile çalıştır
    timeout $TIMEOUT $PHILO $args > "$TEST_DIR/$test_name.log" 2>&1
    local exit_code=$?
    
    # Çıkış kodunu ve çıktıyı kontrol et
    local result=0
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}TIMEOUT: Program sonlanmadı${NC}"
        result=0
    else
        # Özel validasyon fonksiyonunu çağır
        $validation_func "$TEST_DIR/$test_name.log" "$expected_output"
        result=$?
    fi
    
    if [ $result -eq 1 ]; then
        echo -e "${GREEN}✓ Test passed${NC}"
        ((passed_tests++))
    else
        echo -e "${RED}✗ Test failed${NC}"
    fi
    
    print_separator
}

# Validasyon fonksiyonları
validate_death() {
    local log_file=$1
    local expected_time=$2
    
    # Ölüm mesajını kontrol et
    death_line=$(grep "died" $log_file | tail -n 1)
    if [ -z "$death_line" ]; then
        echo -e "${RED}No death message found${NC}"
        return 0
    fi
    
    # Zaman damgasını al
    death_time=$(echo $death_line | awk '{print $1}')
    
    # Birden fazla ölüm mesajını kontrol et
    death_count=$(grep -c "died" $log_file)
    if [ $death_count -ne 1 ]; then
        echo -e "${RED}Multiple death messages ($death_count)${NC}"
        return 0
    fi
    
    # Zaman aralığını kontrol et (izin verilen hata payı ±10ms)
    if [ $death_time -lt $(($expected_time - 10)) ] || [ $death_time -gt $(($expected_time + 10)) ]; then
        echo -e "${RED}Wrong death time: $death_time (expected ~$expected_time)${NC}"
        return 0
    fi
    
    return 1
}

validate_no_death() {
    local log_file=$1
    
    death_count=$(grep -c "died" $log_file)
    if [ $death_count -ne 0 ]; then
        echo -e "${RED}Unexpected death occurred${NC}"
        return 0
    fi
    
    return 1
}

validate_meals() {
    local log_file=$1
    local expected_meals=$2
    
    meals_count=$(grep -c "is eating" $log_file)
    if [ $meals_count -lt $expected_meals ]; then
        echo -e "${RED}Not enough meals: $meals_count (expected $expected_meals)${NC}"
        return 0
    fi
    
    return 1
}

# Test senaryoları
declare -a test_cases=(
    "single_philo 1 800 200 200 validate_death 800"
    "five_philos 5 800 200 200 validate_no_death"
    "five_philos_meals 5 800 200 200 7 validate_meals 35"
    "four_philos 4 410 200 200 validate_no_death"
    "death_test 4 310 200 100 validate_death 310"
    "two_philos 2 800 200 200 validate_no_death"
)

# Testleri çalıştır
for test_case in "${test_cases[@]}"; do
    read -a fields <<< "$test_case"
    test_name=${fields[0]}
    args=${fields[@]:1:$((${#fields[@]}-3))}
    validation_func=${fields[-2]}
    expected_output=${fields[-1]}
    
    run_test "$test_name" "${args}" "$expected_output" "$validation_func"
done

# Özet rapor
print_separator
echo -e "${YELLOW}Test Sonucu: $passed_tests/$total_tests test başarılı${NC}"

# Temizlik
rm -f $TEST_DIR/*.log

exit $((total_tests - passed_tests))