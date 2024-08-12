#pragma once
class CApp;
class CPhone {
private:
	int m_Selection;
	enum AppType {
		MESSAGES, // defines the fucking icon index
		CONTACTS,
		SNAPMATIC,
		WEB,
	};
	enum ButtonIndex {
		//I don't know what goes here its just like the 3 colored buttons on the bottom of scr
	};
	static const int _MAX_APP_ = 9;
	AppType AppScreen[_MAX_APP_]; // 9 slots 8 indexs;
	int PhoneItem;
	
public:
	struct sAppLaunchParams {
		AppType m_App;
		CApp* m_AppInstance; // downcast to the actual app for stuff
	};
	CPhone();
	void Init();
	void SetIndex();
	void OpenApp(sAppLaunchParams& params);
	static void Draw(CPhone* phone);
	void Draw();
	void Destroy();
	~CPhone();
	const char* GetAppFromIndex(AppType index); //return std::string.cstr()
};