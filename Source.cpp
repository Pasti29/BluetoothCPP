#include <iostream>
#include <WinSock2.h>
#include <BluetoothAPIs.h>
#include <ws2bth.h>
#include <stdio.h>
#include <Bthsdpdef.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"irprops.lib")
#pragma warning(disable : 4995)
using namespace std;

HANDLE radio;

HBLUETOOTH_RADIO_FIND radio_find = nullptr;
BLUETOOTH_FIND_RADIO_PARAMS radio_params = { sizeof(radio_params) };

HBLUETOOTH_DEVICE_FIND device_find = nullptr;
BLUETOOTH_DEVICE_SEARCH_PARAMS device_params = { sizeof(device_params) };

BLUETOOTH_DEVICE_INFO device_info[10];

bool isRadioFound = false;

void findRadio() {
	radio_find = BluetoothFindFirstRadio(&radio_params, &radio);
	cout << "     Adapter BT: ";
	if (radio_find == nullptr) {
		cout << " Nieznaleziony" << endl;
		isRadioFound = false;
	}
	else {
		cout << "Znaleziony" << endl;
		isRadioFound = true;

	}
}
void findDevice()
{
	device_params = { sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), 1, 0, 1, 1, 1, 3,
   radio_find };
	int number_of_devices = 0;
	device_info[number_of_devices].dwSize = { sizeof(BLUETOOTH_DEVICE_INFO) };
	device_find = BluetoothFindFirstDevice(&device_params, &device_info[number_of_devices]);
	while (BluetoothFindNextDevice(device_find,
		&device_info[number_of_devices])) {
		cout << "Znaleziono urzadzenie " << number_of_devices << endl << endl;
		cout << "Adres: " << device_info[number_of_devices].Address.ullLong <<
			endl;
		wprintf_s(L"Nazwa: %s\n", device_info[number_of_devices].szName);

		cout << "Nazwa: " << device_info[number_of_devices].szName << endl;
		cout << "Autentykacja: ";
		if (device_info[number_of_devices].fAuthenticated > 0) cout << "True" << endl << endl; else cout << "False" << endl << endl;
		number_of_devices++;
	}
}
void setDevice()
{
	int selected;
	cout << "WPROWADZ NUMER URZADZENIA : ";
	cin >> selected;
	BLUETOOTH_DEVICE_INFO yourDevice = device_info[selected];
#pragma deprecated(BluetoothAuthenticateDevice)
	BluetoothAuthenticateDevice(NULL, radio, &yourDevice, NULL, BLUETOOTH_MAX_PASSKEY_SIZE);
}
void sendfile(BLUETOOTH_DEVICE_INFO yourDevice) {
	string filename;
	cout << "File: ";
	//cin >> filename;
	//Uri uri = new Uri("obex://" + yourDevice.Address.ullLong + "/" + filename);
	//ObexWebRequest request = new ObexWebRequest(uri);
	//request.ReadFile(filename);
	//ObexWebResponse response = (ObexWebResponse)request.GetResponse();
	//response.Close();
}
int main() {
	cout << "Wyszukiwanie adaptera..." << endl;
	findRadio();
	findDevice();
	setDevice();
	return 0;
}
