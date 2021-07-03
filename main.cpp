#include "SelectorController2D.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <Windows.h>
#include <iomanip>
#include <limits>
#undef max
#define WINVER 0x0500
#define NO_DATA_PLANE "ADD PLANE","..."
#define DEF_CALLSIGN "ADD PLANE"

using namespace std;

class Plane {
private:
	string callsign = "N/A";
	string intent = "N/A";
	string aircraft="N/A";
	string clearence="N/A";
	string notes = "N/A";
	bool emergency = false;
public:

	Plane(string callsignIN,string aircraftIN) {
		callsign = callsignIN;
		aircraft = aircraftIN;
	}

	Plane(string callsignIN, string aircraftIN, string intentIN) {
		callsign = callsignIN;
		aircraft = aircraftIN;
		intent = intentIN;
	}

	
	string getCallsign() {
		return callsign;
	}

	void setAircraft(string aircraftIN) {
		aircraft = aircraftIN;
	}
	string getAircraft() {
		return aircraft;
	}
	
	void setIntent(string intentIN) {
		intent = intentIN;
	}
	string getIntent() {
		return intent;
	}

	void setClearence(string clearenceIN) {
		clearence = clearenceIN;
	}
	string getClearence() {
		return clearence;
	}

	void setNotes(string notesIN) {
		notes = notesIN;
	}
	string getNotes() {
		return notes;
	}

	void startEmergency() {
		emergency = true;
		setIntent("EMERGENCY");
		setClearence("ALL");
	}
	void stopEmergency(){
		setIntent("N/A");
		setClearence("N/A");
		emergency = false;
	}

};

SelectorController2D selecControl(1, 1);
vector<Plane> Planes;
int selectedPlane = 0;

void clearKeyboardBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void gotoXY(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void GenerateMainList() {
	system("cls");
	cout << "                              DISPLAY                              " << endl;
	cout << "-------------------------------------------------------------------" << endl;

	if (!Planes.empty()) {

		for (int i = 0; i < Planes.size(); i++) 
			cout <<i+1<< selecControl.Visualizer[0][Planes.size() - 1 - i] << setw(15) << Planes[i].getCallsign() << setw(16) << Planes[i].getIntent() << '|' << "\n";
		
		if (Planes.size() >= 3) {
			gotoXY(34, 2);
			cout << selecControl.Visualizer[1][Planes.size() - 1] << " Aircraft:"<<Planes[selectedPlane].getAircraft();
			gotoXY(34, 3);
			cout << selecControl.Visualizer[1][Planes.size() - 2] << "Clearence:"<<Planes[selectedPlane].getClearence();
			gotoXY(34, 4);
			cout << selecControl.Visualizer[1][Planes.size() - 3] << "    Notes:"<<Planes[selectedPlane].getNotes();
			gotoXY(0, Planes.size()+10);
		}else{
			gotoXY(34, 2);
			cout << selecControl.Visualizer[1][2] << Planes[selectedPlane].getAircraft();
			gotoXY(34, 3);
			cout << selecControl.Visualizer[1][1] << Planes[selectedPlane].getClearence();
			gotoXY(34, 4);
			cout << selecControl.Visualizer[1][0] << Planes[selectedPlane].getNotes();
			gotoXY(0, Planes.size()+10);
		}
	}
}

void resizeCursorController() {
	if (!Planes.empty()) {
		new (&selecControl) SelectorController2D(2, Planes.size(), 0, Planes.size() - 1);
	}
	else new (&selecControl) SelectorController2D(1, 1);
}

void makeNewPlane() {
	Sleep(100);
	gotoXY(0, Planes.size() - selecControl.SelectionY + 1);
	cout << "                                                                                                                  ";
	gotoXY(0, Planes.size() - selecControl.SelectionY + 1);
	cout << "CALLSIGN:";
	string callsign;
	gotoXY(10, Planes.size() - selecControl.SelectionY + 1);
	cin >> callsign;
	gotoXY(callsign.length()+10, Planes.size() - selecControl.SelectionY + 1);
	cout << " AIRCRAFT:";
	string aircraft;
	cin >> aircraft;
	gotoXY(aircraft.length() + callsign.length() + 20, Planes.size() - selecControl.SelectionY + 1);
	cout << " INTENT:";
	string intent;
	clearKeyboardBuffer();
	getline(cin,intent);
	gotoXY(0, Planes.size()+10);

	for (int i = 0; i < 2; i++) {
		if (Planes[i].getCallsign() == DEF_CALLSIGN) {
			Planes.at(i) = Plane(callsign, aircraft,intent);
			goto a;
		}
	}
	
	Planes.push_back({ Plane(callsign,aircraft) });
	iter_swap(Planes.end()-1, Planes.end()-2);
a:
	resizeCursorController();

	GenerateMainList();
}

int main() {
	Planes.push_back({ Plane(NO_DATA_PLANE) });
	Planes.push_back({ Plane(NO_DATA_PLANE) });
	Planes.push_back({ Plane(NO_DATA_PLANE) });
	resizeCursorController();
	GenerateMainList();
	while (true) {
		while (true) {
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				if (selecControl.BumpUp() and selecControl.SelectionX == 0) selectedPlane = Planes.size()- 1 - selecControl.SelectionY;
				Sleep(50);
				GenerateMainList();
				break;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				if (selecControl.BumpDown() and selecControl.SelectionX == 0) selectedPlane = Planes.size()- 1 - selecControl.SelectionY;
				Sleep(50);
				GenerateMainList();
				break;
			}

			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				Sleep(50);
				selecControl.BumpLeft();
				GenerateMainList();
				break;
			}

			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				Sleep(50);
				selecControl.BumpRight();
				GenerateMainList();
				break;
			}

			if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
				Sleep(50);
				if (Planes[selectedPlane].getCallsign() != DEF_CALLSIGN) {
					Planes.erase(Planes.begin() + Planes.size() - 1 - selecControl.SelectionY);
					if (Planes.size() < 3)
						Planes.push_back(Plane(NO_DATA_PLANE));
					resizeCursorController();
					GenerateMainList();
				}

			}

			if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				clearKeyboardBuffer();
				if (selecControl.SelectionX == 0) {
					if (Planes[selectedPlane].getCallsign() == DEF_CALLSIGN) {
						makeNewPlane();
					}
					else {
						gotoXY(18, Planes.size() - selecControl.SelectionY + 1);
						cout << "                ";
						gotoXY(18, Planes.size() - selecControl.SelectionY + 1);
						string intent;
						cin >> intent;
						Planes[selectedPlane].setIntent(intent);
						gotoXY(0, Planes.size() + 10);
						GenerateMainList();
					}
				}
				
				if (selecControl.SelectionX == 1) {
					switch (Planes.size() - selecControl.SelectionY - 1) {
						
					case(0):{
						gotoXY(34, 2);
						cout << "                     ";
						gotoXY(34, 2);
						cout << "Aircraft: ";
						string aircraft;
						cin >> aircraft;
						Planes[selectedPlane].setAircraft(aircraft);
						GenerateMainList();
						clearKeyboardBuffer();
						break;
						}

					case (1):{
						gotoXY(34, 3);
						cout << "                     ";
						gotoXY(34, 3);
						cout << "Clearence: ";
						string clearence;
						cin >> clearence;
						Planes[selectedPlane].setClearence(clearence);
						clearKeyboardBuffer();
						GenerateMainList();
						break;
						}

					case (2): {
						gotoXY(34, 4);
						cout << "                     ";
						gotoXY(34, 4);
						cout << "Notes: ";
						string notes;
						cin >> notes;
						Planes[selectedPlane].setNotes(notes);
						clearKeyboardBuffer();
						GenerateMainList();
						break;
						}

					}

				}

				Sleep(50);
			}
		}
	}
	return 0;
}