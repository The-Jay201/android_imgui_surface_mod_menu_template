#!/bin/bash

# Konfigurasi Warna & Style (Biar mirip web GitHub)
BG_BOX='\033[48;5;235m'     # Latar belakang kotak gelap
TEXT_PUTIH='\033[38;5;255m' # Teks putih cerah
TEXT_ABU='\033[38;5;244m'   # Teks abu-abu deskripsi
HIJAU='\033[0;32m'
KUNING='\033[1;33m'
CYAN='\033[0;36m'
BIRU='\033[0;34m'
NC='\033[0m'               # Reset warna

# 1. Bagian Git Push (Tetap standar)
echo -e "${BIRU}=========================================${NC}"
echo -e "${CYAN} 🛠️  1. MENGIRIM PERUBAHAN KODE KE GITHUB ${NC}"
echo -e "${BIRU}=========================================${NC}"
git add .
if git commit -m "Update kode ImGui lewat Termux" 2>/dev/null; then
    git push origin master
else
    echo -e "${TEXT_ABU}ℹ️  Tidak ada perubahan kode baru. Langsung compile...${NC}"
fi

echo ""
echo -e "${BIRU}=========================================${NC}"
echo -e "${CYAN} 🚀 2. MEMICU SERVER UNTUK COMPILE APK     ${NC}"
echo -e "${BIRU}=========================================${NC}"
gh workflow run build.yml

echo -e "${KUNING}⏳ Menghubungkan ke server cloud GitHub...${NC}"
sleep 4

RUN_ID=$(gh run list --workflow="build.yml" --limit=1 --json databaseId --jq '.[0].databaseId')
if [ -z "$RUN_ID" ] || [ "$RUN_ID" = "null" ]; then
    echo -e "${NC}❌ Gagal mengambil ID pengerjaan.${NC}"
    exit 1
fi

clear # Bersihkan layar biar fokus ke kotak UI GitHub lo

# --- REPLIKA TAMPILAN GITHUB ACTIONS ---
# Bagian Atas: Info Commit & Status Utama
echo -e "${TEXT_PUTIH} 🏠 Summary${NC}"
echo -e "${TEXT_ABU} Semua pekerjaan${NC}"
echo -e ""
echo -e " ┌────────────────────────────────────────────────────────┐"
echo -e " │ Dipicu secara manual | Status: ${KUNING}Sedang berlangsung...${NC}   │"
echo -e " │ ${TEXT_PUTIH}The-Jay201${NC} -> ${TEXT_ABU}master${NC}                                   │"
echo -e " └────────────────────────────────────────────────────────┘"
echo -e ""
echo -e " 📦 ${TEXT_PUTIH}build.yml${NC}"
echo -e " ${TEXT_ABU} pada: workflow_dispatch${NC}"
echo -e ""

# Ambil baris posisi terminal saat ini untuk animasi
posisi_awal=$(tput lines)

detik=0
frames='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'

# Sembunyikan kursor biar animasinya mulus
tput civis
trap "tput cnorm; exit" INT TERM EXIT

while true; do
    # Ambil status real-time dari GitHub
    STATUS=$(gh run view $RUN_ID --json conclusion,status --jq '.status' 2>/dev/null)
    KESIMPULAN=$(gh run view $RUN_ID --json conclusion,status --jq '.conclusion' 2>/dev/null)
    
    # Animasi loading spinner
    frame_index=$((detik % 10))
    current_frame="${frames:frame_index:1}"

    # Hitung menit dan detik biar persis format "1 mnt, 45 dtk"
    menit=$((detik / 60))
    sisa_detik=$((detik % 60))
    if [ $menit -gt 0 ]; then
        DURASI_TEKS="${menit} mnt, ${sisa_detik} dtk"
    else
        DURASI_TEKS="${sisa_detik} dtk"
    fi

    # Cek jika kompilasi sudah selesai
    if [ "$STATUS" = "completed" ]; then
        tput cnorm
        if [ "$KESIMPULAN" = "success" ]; then
            # Cetak kotak sukses (Warna Hijau)
            echo -e "\r \033[K┌────────────────────────────────────────────────────────┐"
            echo -e " │ ${HIJAU}● membangun${NC}               ${TEXT_PUTIH}${DURASI_TEKS}${NC}              │"
            echo -e " └────────────────────────────────────────────────────────┘"
            echo -e "\n${HIJAU}✅ COMPILE BERHASIL SENSEI!${NC}"
            break
        else
            # Cetak kotak gagal (Warna Merah)
            echo -e "\r \033[K┌────────────────────────────────────────────────────────┐"
            echo -e " │ \033[0;31m● membangun (Gagal)${NC}       ${TEXT_PUTIH}${DURASI_TEKS}${NC}              │"
            echo -e " └────────────────────────────────────────────────────────┘"
            exit 1
        fi
    else
        # CETAK KOTAK PROSES BERJALAN (Biar pas posisinya, kita overwrite barisnya pakai \r)
        # Efek warna background kotak diambil dari variabel BG_BOX
        printf "\r \033[K┌────────────────────────────────────────────────────────┐\n"
        printf " │ ${KUNING}%s membangun${NC}             ${TEXT_ABU}%-16s${NC}       │\n" "$current_frame" "$DURASI_TEKS"
        printf " └────────────────────────────────────────────────────────┘"
        
        # Naikkan kursor 2 baris ke atas untuk overwrite di loop berikutnya
        tput cuu 2
        
        sleep 1
        ((detik++))
    fi
done

# Kembali turunkan kursor ke bawah kotak setelah loop selesai
echo ""
echo ""
echo -e "${BIRU}=========================================${NC}"
echo -e "${CYAN} 📥 3. MENDOWNLOAD OTOMATIS APK KE HP     ${NC}"
echo -e "${BIRU}=========================================${NC}"
echo -e "${TEXT_ABU}⏳ Sedang mengunduh berkas APK asli...${NC}"

gh run download $RUN_ID --name="ImGui-Menu-Debug-APK" --dir=/sdcard/Download/ --clobber 2>/dev/null

echo -e "${HIJAU}🎉 SELESAI! Hasil build disimpan ke folder Download HP lo.${NC}"
echo -e "${BIRU}=========================================${NC}"

