// MessageType all type Message we send between server and client
enum MessageType
{
	publicMessage, privateMessage, privateFile, userStatus, requestSendFile, responseSendFile,
	login, responseLogin, signup, responseSignup, loginNotification, logoutNotification
};
