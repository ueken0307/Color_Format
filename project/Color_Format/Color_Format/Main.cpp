﻿
#include<Siv3D.hpp>
#include<cstring>

void gui_process(GUI&, int&, int&, int&);

void Main()
{
	//310,610
	Window::Resize(370, 610);
	Window::SetTitle(L"Color");
	int R = 0, G = 0, B = 0;

	GUI gui(GUIStyle::Default);
	//0,-8
	gui.setPos(60, -8);

	gui.addln(L"color", GUIColorPalette::Create(Color(R, G, B)));

	for (int i = 0; i < 3; ++i) {
		String name;
		if (i == 0)name = L"R";
		if (i == 1)name = L"G";
		if (i == 2)name = L"B";

		gui.add(GUIText::Create(L"   " + name));
		gui.add(name, GUISlider::Create(0, 255, 0));
		gui.addln(name, GUITextField::Create(3));
		gui.textField(name).setText(L"0");
	}

	gui.add(L"line", GUIHorizontalLine::Create(1));

	gui.add(L"type", GUIRadioButton::Create({ L"RGB", L"BGR", L"HTML" }, 0));

	gui.add(GUIText::Create(L"書式"));
	gui.addln(L"format", GUITextArea::Create(3));
	gui.addln(L"output", GUITextArea::Create(3));
	gui.addln(L"auto", GUICheckBox::Create({ L"自動でクリップボードにコピー" }));
	gui.add(L"copy", GUIButton::Create(L"クリップボードにコピー", false));

	while (System::Update())
	{
		gui_process(gui, R, G, B);
		Graphics::SetBackground(Color(R, G, B));
	}
}

void gui_process(GUI &gui, int &R, int &G, int &B) {

	for (int i = 0; i < 3; ++i) {
		String name;
		if (i == 0)name = L"R";
		if (i == 1)name = L"G";
		if (i == 2)name = L"B";

		if (gui.slider(name).hasChanged) {
			gui.textField(name).setText(ToString(gui.slider(name).valueInt));
		}

		if (gui.textField(name).hasChanged) {
			String tmp = gui.textField(name).text;
			if ((tmp.isEmpty) == false) {
				int num = Parse<int>(tmp);
				if (num < 0) {
					num = 0;
				}
				else if (num > 255) {
					num = 255;
				}
				gui.slider(name).setValue(num);
				gui.textField(name).setText(ToString(num));
			}
		}
		if (gui.textField(name).active == false) {
			String tmp = gui.textField(name).text;
			if ((tmp.isEmpty) == true) {
				gui.slider(name).setValue(0);
				gui.textField(name).setText(ToString(0));
			}
		}

	}

	if (gui.colorPalette(L"color").pressed) {
		Color tmp = gui.colorPalette(L"color").color;
		gui.slider(L"R").setValue(tmp.r);
		gui.slider(L"G").setValue(tmp.g);
		gui.slider(L"B").setValue(tmp.b);

		gui.textField(L"R").setText(ToString(tmp.r));
		gui.textField(L"G").setText(ToString(tmp.g));
		gui.textField(L"B").setText(ToString(tmp.b));
	}

	R = gui.slider(L"R").valueInt;
	G = gui.slider(L"G").valueInt;
	B = gui.slider(L"B").valueInt;

	gui.colorPalette(L"color").set(Color(R, G, B));
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	String format = gui.textArea(L"format").text;
	if (gui.radioButton(L"type").checked(2)) {
		gui.textArea(L"format").enabled = false;
		format = String(L"#@@@");
	}
	else {
		gui.textArea(L"format").enabled = true;
	}
	std::string tmp = format.narrow();
	int num = 0;
	int i;
	for (i = 0; i < 3; ++i) {
		num = tmp.find("@", num);
		if (num == -1) {
			break;
		}
		else {
			tmp.erase(tmp.begin() + num);
			if (gui.radioButton(L"type").checked(2)) {
				//HTMLの場合
				tmp.insert(tmp.begin() + num, 'x');
				tmp.insert(tmp.begin() + num, '2');
				tmp.insert(tmp.begin() + num, '0');
			}
			else {
				tmp.insert(tmp.begin() + num, 'd');
			}

			tmp.insert(tmp.begin() + num, '%');
		}
	}
	char out[128];
	gui.button(L"copy").enabled = false;
	if (i == 0) {
		sprintf_s(out, "書式の中に@が含まれていません");
	}
	else if (i == 1) {
		sprintf_s(out, "書式の中に@が１つしかありません");
	}
	else if (i == 2) {
		sprintf_s(out, "書式の中に@が２つしかありません");
	}
	else if (i == 3) {
		gui.button(L"copy").enabled = true;
		if (gui.radioButton(L"type").checked(0)) {
			//RGB
			sprintf_s(out, tmp.c_str(), R, G, B);
		}
		else if (gui.radioButton(L"type").checked(1)) {
			//BGR
			sprintf_s(out, tmp.c_str(), B, G, R);
		}
		else if (gui.radioButton(L"type").checked(2)) {
			//HTML
			sprintf_s(out, tmp.c_str(), R, G, B);
		}
	}

	std::string output(out);
	gui.textArea(L"output").setText(Widen(output));

	if (Window::Focused() == true && i == 3 && gui.checkBox(L"auto").checked(0)) {
		//自動コピー
		gui.button(L"copy").enabled = false;
		Clipboard::SetText(Widen(output));
	}

	if (gui.button(L"copy").pressed) {
		//コピーボタン
		Clipboard::SetText(Widen(output));
	}
}