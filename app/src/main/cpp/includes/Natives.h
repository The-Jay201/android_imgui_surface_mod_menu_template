//
// Created by Laughing Muffin on 22.09.2023
// Modified to Auto-Resize and Custom Text
//======================================================================================================================
#pragma once
//======================================================================================================================
#include <Globals.h>
#include <DrawUtils.h>
//======================================================================================================================
using json = nlohmann::json;
//======================================================================================================================
const char *style_list[11] = {
        OBFUSCATE("Classic"),
        OBFUSCATE("Light"),
        OBFUSCATE("Dark Blue"),
        OBFUSCATE("Green & Blue"),
        OBFUSCATE("Dark Red"),
        OBFUSCATE("Deep Dark"),
        OBFUSCATE("Golden Black"),
        OBFUSCATE("Dark Grey"),
        OBFUSCATE("Grey"),
        OBFUSCATE("Soft Dark Red"),
        OBFUSCATE("Steam Half Life")
};
//======================================================================================================================
struct Variables {
    char StylePath[128] = "";
} Vars;
//======================================================================================================================
struct StyleVariables {
    std::string name = OBFUSCATE("style.json");
    int style_selection = 0;
} StyleVars;
// if you extend the number of vars remember to declare them here too
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StyleVariables, name, style_selection)

//======================================================================================================================
StyleVariables LoadStyles() {
    FILE *file = fopen(Vars.StylePath, OBFUSCATE("r"));
    if (!file) {
        return StyleVars;
    }
    json j;
    try {
        std::ifstream f(Vars.StylePath, std::ifstream::binary);
        f >> j;
        return j.get<StyleVariables>();
    } catch (...) {
        return StyleVars;
    }
}

//======================================================================================================================
void SaveStyle(StyleVariables preset) {
    json j = preset;
    std::ofstream o(Vars.StylePath);
    o << std::setw(4) << j << std::endl;
}

//======================================================================================================================
struct MenuVariables {
    float winWidth = 0.0f;
    float winHeight = 0.0f;
    float winPosWidth = 0.0f;
    float winPosHeight = 0.0f;
    ImVec4 textColor = ImVec4(0.990f, 0.0396f, 0.816f, 1.00f); 
    ImVec4 color_red = ImVec4(1.0f, 0.0f, 0.0f, 1.00f); 
    ImVec4 color_purple = ImVec4(1.0f, 0.0f, 1.0f, 1.00f); 
    ImVec4 color_green = ImVec4(0.0f, 1.0f, 0.0f, 1.00f); 
} MenuVars;
//======================================================================================================================
struct CheatVariables {
    float damageMultiplierF = 1.0f;
    int damageMultiplier = 1;
    int int_radio_A = 0;
    int int_button_math = 0;
    int drag_A = 0;
    int drag_B = 0;
    bool bool_checkbox_A = false;
    bool bool_draw_line = false;
    bool bool_draw_box = false;
} CheatVars;

//======================================================================================================================
void HelpMarker(const char *desc) {
    ImGui::TextDisabled(OBFUSCATE("(?)"));
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 30.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

//======================================================================================================================
void DrawLeftColumn() {
    // Mengatur lebar kolom kiri secara dinamis (proporsional terhadap ukuran jendela saat ini)
    float currentWindowWidth = ImGui::GetWindowWidth();
    ImGui::SetColumnWidth(-1, currentWindowWidth * 0.45f);

    ImGui::Separator();
    ImGui::SeparatorText(OBFUSCATE("##LEFT_COLUMN_TOP_SEPARATOR_1"));

    // Mengubah kata-kata menjadi By The Jay
    ImGui::Text(OBFUSCATE("By The Jay"));
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay..."));

    ImGui::SeparatorText(OBFUSCATE("By The Jay"));

    ImGui::TextWrapped(OBFUSCATE("By The Jay"));

    ImGui::SeparatorText(OBFUSCATE("##LEFT_COLUMN_TOP_SEPARATOR_2"));

    ImGui::TextColored(MenuVars.textColor, OBFUSCATE("By The Jay"));

    ImGui::SeparatorText(OBFUSCATE("##LEFT_COLUMN_TOP_SEPARATOR_3"));
    ImGui::Spacing();
    ImGui::BulletText(OBFUSCATE("By The Jay"));
    ImGui::Spacing();
    ImGui::SeparatorText(OBFUSCATE("##LEFT_COLUMN_TOP_SEPARATOR_4"));

    ImGui::TextDisabled(OBFUSCATE("By The Jay"));

    ImGui::SameLine();
    HelpMarker(OBFUSCATE("By The Jay"));

    ImGui::SeparatorText(OBFUSCATE("##LEFT_COLUMN_TOP_SEPARATOR_5"));
}

//======================================================================================================================
void DrawCheats() {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay"));
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    const char *items_combo[] = {"By The Jay A", "By The Jay B", "By The Jay C"};
    static int item_combo_current = 0;
    ImGui::Text("Combo: ");
    ImGui::SameLine();
    ImGui::Text("%s", items_combo[item_combo_current]);

    ImGui::Combo("##_my_combo", &item_combo_current, items_combo, IM_ARRAYSIZE(items_combo));
    ImGui::SeparatorText("##SEP_MID_1");

    const char *items_list[] = {"By The Jay 1", "By The Jay 2", "By The Jay 3"};
    static int item_list_current = 1;
    ImGui::Text("List: ");
    ImGui::SameLine();
    ImGui::Text("%s", items_list[item_list_current]);
    ImGui::ListBox("##_my_list", &item_list_current, items_list, IM_ARRAYSIZE(items_list), 3);
    ImGui::SeparatorText("##SEP_MID_1");

    ImGui::Text("By The Jay INT");
    ImGui::DragInt("##drag int", &CheatVars.drag_A, 1);
    ImGui::SeparatorText("##SEP_MID_1");

    ImGui::EndTabItem();
}

//======================================================================================================================
void DrawMore() {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay"));
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::TextColored(MenuVars.textColor, "By The Jay Slider INT");
    ImGui::SliderInt("##_dmg", &CheatVars.damageMultiplier, 1, 100);
    ImGui::SameLine();
    HelpMarker("By The Jay");
    ImGui::SameLine();
    ImGui::Text("§ %d", CheatVars.damageMultiplier);
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::TextColored(MenuVars.textColor, "By The Jay Slider FLOAT");
    ImGui::SliderFloat("##_dmg_f", &CheatVars.damageMultiplierF, 1.0f, 10.0f, "%.1f");
    ImGui::SameLine();
    HelpMarker("By The Jay");
    ImGui::SameLine();
    ImGui::Text("§ %.1f", CheatVars.damageMultiplierF);
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::Text("By The Jay Drag");
    ImGui::DragInt("##drag int 0..100_", &CheatVars.drag_B, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SeparatorText("##SEP_MID_1");

    ImGui::EndTabItem();
}

//======================================================================================================================
void DrawEvenMore() {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay"));
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::Checkbox("By The Jay Checkbox", &CheatVars.bool_checkbox_A);
    ImGui::SameLine();
    HelpMarker("By The Jay");
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::RadioButton("By The Jay Off", &CheatVars.int_radio_A, 0);
    ImGui::SameLine();
    ImGui::RadioButton("By The Jay On", &CheatVars.int_radio_A, 1);
    ImGui::SameLine();
    HelpMarker("By The Jay");
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::Button("By The Jay");
    ImGui::SameLine();
    if (ImGui::Button("By The Jay Math")) {
        CheatVars.int_button_math++;
    }
    ImGui::SameLine();
    HelpMarker("By The Jay");
    ImGui::SameLine();
    ImGui::Text("Count: %d", CheatVars.int_button_math);
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::Checkbox("By The Jay Line", &CheatVars.bool_draw_line);
    ImGui::SameLine();
    ImGui::Checkbox("By The Jay Box", &CheatVars.bool_draw_box);
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::EndTabItem();
}

//======================================================================================================================
void DrawStyleEditor() {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay Style"));
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_1"));

    ImGui::Spacing();
    ImGui::Text(OBFUSCATE("By The Jay Picker"));
    ImGui::Combo(OBFUSCATE("##Default Style Picker"), &StyleVars.style_selection, style_list, IM_ARRAYSIZE(style_list), 15);
    ImGui::Spacing();
    if (ImGui::Button(OBFUSCATE("Save Config"), ImVec2(170, 50))) {
        SaveStyle(StyleVars);
    }

    ImGui::EndTabItem();
}

//======================================================================================================================
void DrawOtherStuff() {
    ImGui::SeparatorText(OBFUSCATE("##SEP_MID_0"));

    if (ImGui::BeginTabBar("_tab_bar", ImGuiTabBarFlags_FittingPolicyScroll)) {
        if (ImGui::BeginTabItem("By The Jay 1", NULL, ImGuiTabItemFlags_Leading)) {
            DrawCheats();
        }
        if (ImGui::BeginTabItem("By The Jay 2")) {
            DrawMore();
        }
        if (ImGui::BeginTabItem("By The Jay 3")) {
            DrawEvenMore();
        }
        if (ImGui::BeginTabItem("By The Jay Style")) {
            DrawStyleEditor();
        }
        ImGui::EndTabBar();
    }
}

//======================================================================================================================
void DrawEsp() {
    if (CheatVars.bool_draw_line) {
        DrawLine({0, 0}, {250, 550}, MenuVars.color_red);
        DrawText({252, 500}, MenuVars.color_purple, "[X] By The Jay Line", 30.0f);
    }
    if (CheatVars.bool_draw_box) {
        DrawBox({250, 550}, {350, 650}, MenuVars.color_green);
        DrawText({350, 650}, MenuVars.color_red, "[X] By The Jay Box", 30.0f);
    }
}

//======================================================================================================================
void DrawColumnsDrivenMenu() {
    // --- FITUR AUTO RESIZE & SCALING AGAR TIDAK MEMENUHI LAYAR ---
    ImGuiIO& io = ImGui::GetIO();
    
    // Mengambil resolusi layar HP secara dinamis
    float screenWidth = io.DisplaySize.x;
    float screenHeight = io.DisplaySize.y;

    // Mengatur skala global elemen UI (0.8f berarti diperkecil menjadi 80% dari ukuran default)
    ImGui::GetStyle().ScaleAllSizes(0.8f);
    
    // Menghitung ukuran jendela menu yang ideal (misal: 75% dari lebar layar dan 65% dari tinggi layar)
    float idealWidth = screenWidth * 0.75f;
    float idealHeight = screenHeight * 0.65f;
    
    // Memposisikan menu tepat di tengah-tengah layar secara otomatis
    float posX = (screenWidth - idealWidth) * 0.5f;
    float posY = (screenHeight - idealHeight) * 0.5f;

    // Terapkan ukuran dan posisi yang baru sebelum menggambar window menu utama
    ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(idealWidth, idealHeight), ImGuiCond_Always);

    ImGui::Columns(2);
    DrawLeftColumn();
    ImGui::NextColumn();
    DrawOtherStuff();
    DrawEsp();
}
