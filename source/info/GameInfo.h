
namespace info {
	class GameInfo {
		public:
			GameInfo(char* aName, char* aCreator);
			~GameInfo(void);

			char* getName();
			char* getCreator();
	};
}
