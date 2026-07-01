#!/bin/bash

# Efek Warna
HIJAU='\033[0;32m'
BIRU='\033[0;34m'
KUNING='\033[1;33m'
CYAN='\033[0;36m'
MERAH='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BIRU}=========================================${NC}"
echo -e "${CYAN} 🛠️  1. MENGIRIM PERUBAHAN KODE KE GITHUB ${NC}"
echo -e "${BIRU}=========================================${NC}"
git add .
if git commit -m "Update kode ImGui lewat Termux" 2>/dev/null; then
    git push origin master
else
    echo -e "${KUNING}ℹ️  Tidak ada perubahan kode baru. Langsung compile...${NC}"
fi

echo ""
echo -e "${BIRU}=========================================${NC}"
echo -e "${CYAN} 🚀 2. MEMICU SERVER UNTUK COMPILE APK     ${NC}"
echo -e "${BIRU}=========================================${NC}"
gh workflow run build.yml

echo -e "${KUNING}⏳ Menghubungkan ke server cloud GitHub...${NC}"
# Animasi loading sederhana selama 8 detik untuk menunggu server membuat RUN_ID
spin='-\|/'
for ((i=0; i<32; i++)); do
    printf "\r[%c] Mempersiapkan lingkungan server..." "${spin:i%4:1}"
    sleep 0.25
done
echo -e "\n"

# Mengambil ID proses run terbaru
RUN_ID=$(gh run list --workflow="build.yml" --limit=1 --json databaseId --jq '.[0].databaseId')

if [ -z "$RUN_ID" ] || [ "$RUN_ID" = "null" ]; then
    echo -e "${MERAH}❌ Gagal mengambil ID pengerjaan dari GitHub. Coba jalankan ulang!${NC}"
    exit 1
fi

echo -e "${HIJAU}✅ Terhubung! ID Pengerjaan Cloud: $RUN_ID${NC}"
echo -e "${BIRU}-----------------------------------------${NC}"

# Hitung waktu (detik) dan animasi loading berputar
detik=0
frames='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'

while true; do
    # Ambil status pengerjaan secara real-time
    STATUS=$(gh run view $RUN_ID --json conclusion,status --jq '.status')
    KESIMPULAN=$(gh run view $RUN_ID --json conclusion,status --jq '.conclusion')
    
    # Animasi frame berputar
    frame_index=$((detik % 10))
    current_frame="${frames:frame_index:1}"

    if [ "$STATUS" = "completed" ]; then
        if [ "$KESIMPULAN" = "success" ]; then
            echo -e "\n\n${HIJAU}✅ COMPILE BERHASIL! (Waktu: $detik detik)${NC}"
            break
        else
            echo -e "\n\n${MERAH}❌ COMPILE GAGAL! Periksa kembali kodingan ImGui kamu.${NC}"
            exit 1
        fi
    else
        # Tampilkan penghitung waktu mundur/maju yang bergerak di satu baris yang sama
        printf "\r\r${KUNING}%s [Memproses di Cloud] Waktu berjalan: %d detik (Status Server: %s)...${NC}" "$current_frame" "$detik" "$STATUS"
        sleep 1
        ((detik++))
    fi
done

echo ""
echo -e "${BIRU}=========================================${

