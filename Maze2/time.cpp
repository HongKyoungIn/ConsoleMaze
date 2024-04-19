#include "time.h"
#include "Windows.h"

namespace global {
	namespace time {
		ULONGLONG previousTime;
		ULONGLONG currentTime;
		ULONGLONG deltaTime;

		int updateCount;
		int fixedUpdateCount;

		void InitTime() {
			previousTime = currentTime = GetTickCount64();
		}

		void UpdateTime() {
			previousTime = currentTime;

			currentTime = GetTickCount64();

			deltaTime = currentTime - previousTime;
		}

		ULONGLONG GetDeltaTime() {
			return deltaTime;
		}
	}
}