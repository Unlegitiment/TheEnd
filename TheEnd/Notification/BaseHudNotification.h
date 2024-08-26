#pragma once
class CNotification {
public:
	virtual void Send(const char* m_buffer);
private:
	const char* m_Notification;
	unsigned long long guidComponent;
	int g_Handle;
};