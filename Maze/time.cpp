#include "time.h"
#include <cmath>
#include <Windows.h>

namespace myTime {
	ULONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime;
	ULONGLONG playStartTime; // �÷��� ���� �ð�
	const int DEBOUNCE_DELAY = 100; // �Է� ��ٿ ���� (�и���)
	DWORD lastInputTime = GetTickCount64(); // ������ �Է� �ð��� �����ϴ� ����

	void InitTime() {
		previousTime = currentTime = GetTickCount64();
		playStartTime = previousTime;
	}

	void UpdateTime() {
		previousTime = currentTime;
		currentTime = GetTickCount64();
		deltaTime = currentTime - previousTime;
	}

	int PlayTime() {
		int currentPlayTime = GetTickCount64() - playStartTime; // ���� �÷��� Ÿ�� ���
		return currentPlayTime;
	}

	const float GetFrameRate() {
		if(deltaTime == 0) {
			return 0;
		}

		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
	}

	const ULONGLONG GetDeltaTime() {
		return deltaTime;
	}

	bool shouldProcessInput() {
		DWORD currentTime = GetTickCount64(); // ���� �ð� ��������

		// �Է� ��ٿ ���� �̳��� ���ο� �Է��� �����Ǹ� ó������ ����
		if(currentTime - lastInputTime < DEBOUNCE_DELAY) {
			return true; // �Է��� ó��
		}

		// �Է��� ó���� �� �ִ� ���, ������ �Է� �ð��� ������Ʈ
		lastInputTime = currentTime;
		return false; // �Է��� ó������ ����
	}
}