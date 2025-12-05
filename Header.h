#pragma once

using namespace std;

	class coreFunctions
	{
	public:
		int modeType = 0;
		int emoteActionPerformed = 0;
		int intervalTimer = 15000;
		int totalIntervalTimer = 15000;
		int x = 0;
		int y = 0;
		bool clickingStarted = false;
		bool waitForInput = true;

		void coreinit()
		{
			system("TITLE Autoclicker for Emotes");
			cout << "Select an emote to be spammed by typing a number (1-5) and pressing enter." << endl;
			cout << "Acceptable emotes: belfrude (1) , belfchicken (2) , nelfchicken (3) , nelfrude (4) , CUSTOM (5)" << endl;
			cout << "" << endl;
			cout << "IMPORTANT: Before pressing F5 to start clicking, ensure your mouse pointer is in already in position" << endl;
			cin >> emoteActionPerformed;
			cout << "" << endl;

			coreFunctions obj;

			if (emoteActionPerformed == 1)
			{
				intervalTimer = 2650;
				cout << "belfrude (1) selected. Interval is set to " << intervalTimer << endl;
				fnc_clickingOnly(emoteActionPerformed);
			}

			if (emoteActionPerformed == 2)
			{
				intervalTimer = 2650;
				cout << "belfchicken (2) selected. Interval is set to " << intervalTimer << endl;
				fnc_clickingOnly(emoteActionPerformed);
			}

			if (emoteActionPerformed == 3)
			{
				intervalTimer = 2650;
				cout << "nelfchicken (3) selected. Interval is set to " << intervalTimer << endl;
				fnc_clickingOnly(emoteActionPerformed);

			}

			if (emoteActionPerformed == 4)
			{
				intervalTimer = 2650;
				cout << "nelfrude (4) selected. Interval is set to " << intervalTimer << endl;
				fnc_clickingOnly(emoteActionPerformed);
			}

			if (emoteActionPerformed == 5)
			{
				cout << "CUSTOM selected. Please input your desired time in milliseconds" << endl;
				fnc_clickingOnly(emoteActionPerformed);
			}
		}
		
		void fnc_beginClickingLoop(int x, int y, int totalIntervalTimer)
		{
			coreFunctions coreObj;

			coreObj.clickingStarted = true;

			while (coreObj.clickingStarted == true)
			{
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					cout << "Exiting autoclicker";
					coreObj.clickingStarted = false;
					Sleep(150);
					exit(0);
				}
				else
				{
					SetCursorPos(x, y);
					mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
					Sleep(totalIntervalTimer); //wait before clicking for totalIntervalTimer (milliseconds)
				}

			}

		}
		

		void fnc_clickingOnly(int emoteActionPerformed)
		{
	   	   coreFunctions coreObj;

			switch (emoteActionPerformed)
			{
			case 1:
				coreObj.totalIntervalTimer = 2650;
				break;
			case 2:
				coreObj.totalIntervalTimer = 3095;
				break;
			case 3:
				coreObj.totalIntervalTimer = 3300;
				break;
			case 4:
				coreObj.totalIntervalTimer = 2650;
				break;
			case 5:
				cout << "Please enter your custom interval timer (in ms) " << endl;
				cin >> intervalTimer;
				coreObj.totalIntervalTimer = intervalTimer;
				break;
			}

			cout << "Press F5 to save mouse location and begin clicking!" << endl;


			while (waitForInput == true) {
				if (GetAsyncKeyState(VK_F5))
				{
					cout << "Clicking started! Press ESC to close the clicker completely" << endl;
					cout << "Saving current position of mouse" << endl;

					POINT cursorPos;
					GetCursorPos(&cursorPos);
					coreObj.x = cursorPos.x;
					coreObj.y = cursorPos.y;
					cout << "Mouse position X saved as : " << coreObj.x << endl;
					cout << "Mouse position Y saved as : " << coreObj.y << endl;

					fnc_beginClickingLoop(coreObj.x, coreObj.y, coreObj.totalIntervalTimer);

					waitForInput = false;
					

				}
			}

		}


	};
