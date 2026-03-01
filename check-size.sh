#!/bin/bash
echo "=== ФИНАЛЬНАЯ ПРОВЕРКА РАЗМЕРА ==="
echo ""

# ЧТО БУДЕТ В КОММИТЕ
echo "1. ФАЙЛЫ ДЛЯ КОММИТА:"
git diff --cached --name-only | wc -l
echo ""

# РАЗМЕР ПО ТИПАМ ФАЙЛОВ
echo "2. РАЗМЕР ПО ТИПАМ:"
git diff --cached --name-only | while read file; do
    size=$(du -b "$file" 2>/dev/null | awk '{print $1}')
    ext="${file##*.}"
    echo "$ext $size" >> /tmp/sizes.txt
done 2>/dev/null

sort /tmp/sizes.txt | awk '
{ sizes[$1] += $2; count[$1]++ }
END {
    for (ext in sizes) {
        printf "  %-10s: %6d файлов, %8.2f MB\n", 
            ext, count[ext], sizes[ext]/1024/1024
    }
}' | sort -k4 -nr
rm -f /tmp/sizes.txt

echo ""
echo "3. ОБЩИЙ РАЗМЕР:"
total=$(git diff --cached --name-only | xargs -I {} du -b {} 2>/dev/null | awk '{sum+=$1} END {print sum}')
echo "   $((total/1024/1024)) MB ($total bytes)"

# ЛИМИТЫ
echo ""
echo "4. РЕКОМЕНДАЦИИ:"
if [ $total -gt 52428800 ]; then  # 50MB
    echo "   ⚠️  СЛИШКОМ БОЛЬШО! (>50MB)"
    echo "   УДАЛИТЕ: external/glm/ если есть"
elif [ $total -gt 10485760 ]; then  # 10MB
    echo "   ✅ НОРМАЛЬНО (10-50MB)"
else
    echo "   ✅ ОТЛИЧНО! (<10MB)"
fi
