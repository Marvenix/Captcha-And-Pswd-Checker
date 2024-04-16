#pragma once
#ifdef _MSC_VER
#  pragma warning(disable : 4146)
#endif
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <regex>
#include <string>
#include <filesystem>
#include <gmp.h>
#include <random>

namespace fs = std::filesystem;

class GUI {
public:
    tgui::EditBox::Ptr editBoxPassword;
    tgui::ProgressBar::Ptr ProgressBar;
    tgui::Button::Ptr Button;
    tgui::Button::Ptr ButtonChld1;
    tgui::Button::Ptr ButtonChld2;
    tgui::ChildWindow::Ptr ChildWindow;
    tgui::Picture::Ptr Picture1;
    tgui::Picture::Ptr Picture2;
    tgui::Picture::Ptr Picture3;
    tgui::Picture::Ptr Picture4;
    tgui::Picture::Ptr Picture5;
    tgui::Picture::Ptr Picture6;
    tgui::Picture::Ptr Picture7;
    tgui::Picture::Ptr Picture8;
    tgui::Picture::Ptr Picture9;
    tgui::Label::Ptr Label;
    tgui::Label::Ptr Label2;
    void updateTextSize(tgui::GuiBase& gui)
    {
        const float windowHeight = gui.getView().getRect().height;
        gui.setTextSize(static_cast<unsigned int>(0.05f * windowHeight));
    }
    void Initiate(tgui::GuiBase& gui) {
        updateTextSize(gui);

        gui.onViewChange([&gui] { const float windowHeight = gui.getView().getRect().height;
        gui.setTextSize(static_cast<unsigned int>(0.05f * windowHeight)); });

        auto picture = tgui::Picture::create("a.jpg");
        picture->setSize({ "100%", "100%" });
        gui.add(picture);
    }
};

class Password : public GUI {
public:
    void AddElements(tgui::GuiBase& gui) {
        editBoxPassword = tgui::EditBox::create();
        editBoxPassword->setSize({ "60%", "5%" });
        editBoxPassword->setPosition({ "20%", "8%" });
        editBoxPassword->setPasswordCharacter('*');
        editBoxPassword->setDefaultText("Password");
        gui.add(editBoxPassword);

        ProgressBar = tgui::ProgressBar::create();
        ProgressBar->setSize({ "60%", "5%" });
        ProgressBar->setPosition({ "20%", "15%" });

        gui.add(ProgressBar);

        CheckPassword();
    }
    void CheckPassword() {
        editBoxPassword->onTextChange([this](auto password) {
            auto a = password->getText();
            int wykladnik = 0;
            std::cout << "Password: " << a;
            const std::regex cyfry("[0-9]");
            const std::regex mlitery("[a-z]");
            const std::regex dlitery("[A-Z]");
            const std::regex specjalne("[^A-Za-z0-9]");
            if (std::regex_search(a.toStdString(), cyfry)) { wykladnik += 10; }
            if (std::regex_search(a.toStdString(), mlitery)) { wykladnik += 26; }
            if (std::regex_search(a.toStdString(), dlitery)) { wykladnik += 26; }
            if (std::regex_search(a.toStdString(), specjalne)) { wykladnik += 33; }
            mpz_t kombinacje, wynik1, wynik2, wynik3, wynik4;
            mpz_init(kombinacje);
            mpz_init(wynik1);
            mpz_init(wynik2);
            mpz_init(wynik3);
            mpz_init(wynik4);
            mpz_set_str(wynik1, "1", 0);
            mpz_set_str(wynik2, "15768000000000000000", 0);
            mpz_set_str(wynik3, "78840000000000000000", 0);
            mpz_set_str(wynik4, "236520000000000000000", 0);
            mpz_set_d(kombinacje, pow(wykladnik, a.length()));

            std::cout << " Kombinacje: " << kombinacje << "\n";

            if (mpz_cmp(kombinacje, wynik1) == 0) {
                ProgressBar->setValue(0);
            }
            else if (mpz_cmp(kombinacje, wynik2) < 0) {
                ProgressBar->setValue(25);
                ProgressBar->getRenderer()->setFillColor(sf::Color::Red);
            }
            else if (mpz_cmp(kombinacje, wynik3) < 0) {
                ProgressBar->setValue(50);
                ProgressBar->getRenderer()->setFillColor(sf::Color::Color(255, 165, 0));
            }
            else if (mpz_cmp(kombinacje, wynik4) < 0) {
                ProgressBar->setValue(75);
                ProgressBar->getRenderer()->setFillColor(sf::Color::Yellow);
            }
            else {
                ProgressBar->setValue(100);
                ProgressBar->getRenderer()->setFillColor(sf::Color::Green);
            }
            mpz_clear(kombinacje);
            mpz_clear(wynik1);
            mpz_clear(wynik2);
            mpz_clear(wynik3);
            mpz_clear(wynik4);
            }, editBoxPassword);
    }
};

class Test : public GUI {
public:
    std::vector<std::string> Wejscie;
    std::vector<std::string> Losowane;
    std::vector<int> Licz = { 0,0,0,0,0,0,0,0,0 };
    std::vector<char> Category;
    double Calosc = 0;
    double Dobre = 0;
    int Krok = 0;
    char Chosen;
    void Load() {
        fs::path pth("C:/Users/Inspiron 7000/source/repos/ProjektPK4/ProjektPK4/ProjektPK4/Obrazy");
        if (exists(pth))
        {
            if (is_directory(pth))
            {
                for (auto& e : fs::recursive_directory_iterator(pth))
                {
                    if (e.path().extension() == ".jpg" || e.path().extension() == ".jpeg" || e.path().extension() == ".png") {
                        Wejscie.push_back("Obrazy/" + e.path().filename().string());
                    }
                }
            }
        }
    }
    void Random() {
        std::string tmp = "";
        Losowane.clear();
        Category.clear();
        std::sample(Wejscie.begin(), Wejscie.end(), std::back_inserter(Losowane), 9, std::mt19937{ std::random_device{}() });
        for (int i = 0; i < 9;++i) {
            tmp = Losowane[i];
            Category.push_back(tmp[7]);
        }
    }
    void Work(const std::string& name) {
        if (name == "Picture1") {
            if (Licz[0] % 2 == 1) Picture1->setInheritedOpacity(100);
            if (Licz[0] % 2 == 0) Picture1->setInheritedOpacity(1);
        }
        if (name == "Picture2") {
            if (Licz[1] % 2 == 1) Picture2->setInheritedOpacity(100);
            if (Licz[1] % 2 == 0) Picture2->setInheritedOpacity(1);
        }
        if (name == "Picture3") {
            if (Licz[2] % 2 == 1) Picture3->setInheritedOpacity(100);
            if (Licz[2] % 2 == 0) Picture3->setInheritedOpacity(1);
        }
        if (name == "Picture4") {
            if (Licz[3] % 2 == 1) Picture4->setInheritedOpacity(100);
            if (Licz[3] % 2 == 0) Picture4->setInheritedOpacity(1);
        }
        if (name == "Picture5") {
            if (Licz[4] % 2 == 1) Picture5->setInheritedOpacity(100);
            if (Licz[4] % 2 == 0) Picture5->setInheritedOpacity(1);
        }
        if (name == "Picture6") {
            if (Licz[5] % 2 == 1) Picture6->setInheritedOpacity(100);
            if (Licz[5] % 2 == 0) Picture6->setInheritedOpacity(1);
        }
        if (name == "Picture7") {
            if (Licz[6] % 2 == 1) Picture7->setInheritedOpacity(100);
            if (Licz[6] % 2 == 0) Picture7->setInheritedOpacity(1);
        }
        if (name == "Picture8") {
            if (Licz[7] % 2 == 1) Picture8->setInheritedOpacity(100);
            if (Licz[7] % 2 == 0) Picture8->setInheritedOpacity(1);
        }
        if (name == "Picture9") {
            if (Licz[8] % 2 == 1) Picture9->setInheritedOpacity(100);
            if (Licz[8] % 2 == 0) Picture9->setInheritedOpacity(1);
        }
    }
    void Click() {
        Picture1->onClick([this] {Licz[0]++; Work("Picture1"); });
        Picture2->onClick([this] {Licz[1]++; Work("Picture2"); });
        Picture3->onClick([this] {Licz[2]++; Work("Picture3"); });
        Picture4->onClick([this] {Licz[3]++; Work("Picture4"); });
        Picture5->onClick([this] {Licz[4]++; Work("Picture5"); });
        Picture6->onClick([this] {Licz[5]++; Work("Picture6"); });
        Picture7->onClick([this] {Licz[6]++; Work("Picture7"); });
        Picture8->onClick([this] {Licz[7]++; Work("Picture8"); });
        Picture9->onClick([this] {Licz[8]++; Work("Picture9"); });
    }
    void SetPictures() {
        Picture1->getRenderer()->setTexture(tgui::Texture(Losowane[0]));
        Picture1->setInheritedOpacity(1);
        Picture2->getRenderer()->setTexture(tgui::Texture(Losowane[1]));
        Picture2->setInheritedOpacity(1);
        Picture3->getRenderer()->setTexture(tgui::Texture(Losowane[2]));
        Picture3->setInheritedOpacity(1);
        Picture4->getRenderer()->setTexture(tgui::Texture(Losowane[3]));
        Picture4->setInheritedOpacity(1);
        Picture5->getRenderer()->setTexture(tgui::Texture(Losowane[4]));
        Picture5->setInheritedOpacity(1);
        Picture6->getRenderer()->setTexture(tgui::Texture(Losowane[5]));
        Picture6->setInheritedOpacity(1);
        Picture7->getRenderer()->setTexture(tgui::Texture(Losowane[6]));
        Picture7->setInheritedOpacity(1);
        Picture8->getRenderer()->setTexture(tgui::Texture(Losowane[7]));
        Picture8->setInheritedOpacity(1);
        Picture9->getRenderer()->setTexture(tgui::Texture(Losowane[8]));
        Picture9->setInheritedOpacity(1);
    }
    void Ask() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 8);
        Chosen = Category[dist(gen)];
        switch (Chosen) {
        case 'a':
            Label->setText("Zaznacz: auto");
            break;
        case 'h':
            Label->setText("Zaznacz: hydrant");
            break;
        case 'p':
            Label->setText("Zaznacz: pasy");
            break;
        case 's':
            Label->setText("Zaznacz: swiatla");
            break;
        }
        for (int i = 0; i < 9; ++i) {
            if (Category[i] == Chosen) {
                Calosc++;
            }
        }
    }
    void Passed() {
        ChildWindow->removeAllWidgets();
        Label2 = tgui::Label::create("Nie jestes robotem");
        Label2->setPosition("225", "10");
        ChildWindow->add(Label2);
    }
    void NotPassed() {
        ChildWindow->removeAllWidgets();
        Label2 = tgui::Label::create("Nie przeszedles testu");
        Label2->setPosition("225", "10");
        ChildWindow->add(Label2);
    }
    void Algorithm() {
        Krok++;
        if (Licz[0] % 2 == 1) {
            if (Category[0] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[1] % 2 == 1) {
            if (Category[1] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[2] % 2 == 1) {
            if (Category[2] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[3] % 2 == 1) {
            if (Category[3] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[4] % 2 == 1) {
            if (Category[4] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[5] % 2 == 1) {
            if (Category[5] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[6] % 2 == 1) {
            if (Category[6] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[7] % 2 == 1) {
            if (Category[7] == Chosen) {
                Dobre++;
            }
        }
        if (Licz[8] % 2 == 1) {
            if (Category[8] == Chosen) {
                Dobre++;
            }
        }
        if (Krok > 1) {
            if ((Dobre / Calosc) * 100 >= 80) {
                Passed();
            }
            else if (Krok == 10) {
                NotPassed();
            }
        }
    }
    void ButtonsWork() {
        ButtonChld1->onPress([this] {
            Krok = 0;
            Calosc = 0;
            Dobre = 0;
            Licz = { 0,0,0,0,0,0,0,0,0 };
            Random();
            SetPictures();
            Ask();
            });
        ButtonChld2->onPress([this] {
            Algorithm();
            Licz = { 0,0,0,0,0,0,0,0,0 };
            Random();
            SetPictures();
            Ask();
            });
    }
    void AddElements(tgui::GuiBase& gui) {
        Button = tgui::Button::create("Test");
        Button->setSize({ "20%", "10%" });
        Button->setPosition({ "40%", "45%" });
        gui.add(Button);
    }
    void OpenWindow(tgui::GuiBase& gui) {
        Button->onPress([this, &gui] {
            Krok = 0;
            Calosc = 0;
            Dobre = 0;
            Licz = { 0,0,0,0,0,0,0,0,0 };
            ChildWindow = tgui::ChildWindow::create();
            ChildWindow->setSize("100%", "100%");
            auto panel = tgui::Panel::create({ "100%", "100%" });
            panel->getRenderer()->setBackgroundColor({ 0, 0, 0, 175 });
            gui.add(panel);
            panel->add(ChildWindow);
            ChildWindow->onClose([&gui, panel] { gui.remove(panel); });
            AddElementsChld();
            });
    }
    void AddElementsChld() {
        Label = tgui::Label::create();
        Label->setPosition("225", "10");
        Label->setSize("350", "40");
        Picture1 = tgui::Picture::create();
        Picture1->setPosition("225", "50");
        Picture1->setSize("100", "100");
        Picture2 = tgui::Picture::create();
        Picture2->setPosition("350", "50");
        Picture2->setSize("100", "100");
        Picture3 = tgui::Picture::create();
        Picture3->setPosition("475", "50");
        Picture3->setSize("100", "100");
        Picture4 = tgui::Picture::create();
        Picture4->setPosition("225", "175");
        Picture4->setSize("100", "100");
        Picture5 = tgui::Picture::create();
        Picture5->setPosition("350", "175");
        Picture5->setSize("100", "100");
        Picture6 = tgui::Picture::create();
        Picture6->setPosition("475", "175");
        Picture6->setSize("100", "100");
        Picture7 = tgui::Picture::create();
        Picture7->setPosition("225", "300");
        Picture7->setSize("100", "100");
        Picture8 = tgui::Picture::create();
        Picture8->setPosition("350", "300");
        Picture8->setSize("100", "100");
        Picture9 = tgui::Picture::create();
        Picture9->setPosition("475", "300");
        Picture9->setSize("100", "100");
        ButtonChld1 = tgui::Button::create("Reset");
        ButtonChld1->setPosition("225", "425");
        ButtonChld1->setSize("170", "35");
        ButtonChld2 = tgui::Button::create("Dalej");
        ButtonChld2->setPosition("405", "425");
        ButtonChld2->setSize("170", "35");
        ChildWindow->add(Label);
        ChildWindow->add(Picture1);
        ChildWindow->add(Picture2);
        ChildWindow->add(Picture3);
        ChildWindow->add(Picture4);
        ChildWindow->add(Picture5);
        ChildWindow->add(Picture6);
        ChildWindow->add(Picture7);
        ChildWindow->add(Picture8);
        ChildWindow->add(Picture9);
        ChildWindow->add(ButtonChld1);
        ChildWindow->add(ButtonChld2);
        Click();
        ButtonsWork();
        if (Wejscie.size() >= 9) {
            Random();
            SetPictures();
            Ask();
        }
    }
};
