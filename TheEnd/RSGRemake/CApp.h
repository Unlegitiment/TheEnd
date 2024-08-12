#pragma once
template<class __App>
class CApp {
protected:
	enum AppType {
		AI_MESSAGE_LIST,
		AI_MESSAGE_VIEW,
		AI_CALLSCREEN,
		AI_CONTACTS,
		AI_EMAIL_LIST,
		AI_EMAIL_VIEW,
		AI_INTERNET,
		AI_JOB_LIST,
		AI_JOB_VIEW,
		AI_SNAPMATIC,
		AI_GAMEMODE_LIST,
		AI_GAMEMODE_SELECT, // Friends In Session, Alone
	};
public:
	CApp();
protected:
	AppType GetType();
	void SetType(AppType _type);
	__App* GetClass();
	CApp* GetBase();
	CApp(AppType type);
private:
	AppType m_AppType;
	

};

template<class __App>
inline CApp<__App>::CApp() {
}
template<class __App>
inline CApp<__App>::AppType CApp<__App>::GetType() {
	return m_AppType;
}

template<class __App>
inline void CApp<__App>::SetType(AppType _type) {
}

template<class __App>
inline __App* CApp<__App>::GetClass() {
	return static_cast<__App*>(this);
}

template<class __App>
inline CApp<__App>* CApp<__App>::GetBase() {
	return this;
}

template<class __App>
inline CApp<__App>::CApp(AppType type) {
}
