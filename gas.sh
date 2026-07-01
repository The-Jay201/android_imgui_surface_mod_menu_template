#!/bin/bash

echo "========================================="
echo "1. Mengirim perubahan kode ke GitHub..."
echo "========================================="
git add .
git commit -m "Update kode ImGui lewat Termux"
git push origin master

echo ""
echo "========================================="
echo "2. Memperintahkan Server GitHub untuk Compile..."
echo "========================================="
# Menjalankan github action secara remote
gh workflow run "Android CI Build"

echo "Menunggu server merespon..."
sleep 10

# Mengambil ID proses run terbaru
RUN_ID=$(gh run list --workflow="build.yml" --limit=1 --json databaseId --jq '.[0].databaseId')

echo "Proses Compile sedang berjalan di Cloud (ID: $RUN_ID)"
echo "Mohon tunggu, ini memakan waktu sekitar 3-5 menit..."
echo "Jangan tutup Termux!"
echo "-----------------------------------------"

# Melakukan cek status setiap 20 detik sampai selesai
while true; do
    STATUS=$(gh run view $RUN_ID --json conclusion --jq '.conclusion')
    if [ "$STATUS" = "success" ]; then
        echo "✅ Compile SUKSES!"
        break
    elif [ "$STATUS" = "failure" ]; then
        echo "❌ Compile GAGAL! Periksa kembali kodingan ImGui kamu."
        exit 1
    else
        echo "Masih memproses... (Status: $STATUS)"
        sleep 20
    fi
done

echo ""
echo "========================================="
echo "3. Mendownload otomatis file APK ke HP..."
echo "========================================="
# Download hasil artifact dan langsung simpan ke folder Download HP kamu
gh run download $RUN_ID --name="ImGui-Menu-Debug-APK" --dir=/sdcard/Download/

echo "🎉 SelesAI! File ZIP APK sudah ada di folder Download HP kamu."
echo "Silakan cek folder Download dan ekstrak filenya."
echo "========================================="

