#pragma once
#include "Configs.h"

namespace core
{
	class CObjectPoolMonitor
	{
		static std::map<std::string, std::function<void()>> ObjectPoolMap;
	public:
		static void monitorPool(std::string name, std::function<void()>&& func)
		{
			ObjectPoolMap[name] = std::move(func);
		}

		static void delMonitorPool(const std::string& name)//?
		{
			ObjectPoolMap.erase(name);
		}

		static void showInfo()
		{
			core_log_info("ObjectPoolInfo Start", TimeHelp::TimeToString(TimeHelp::now()));
			for (const auto&iter : ObjectPoolMap)
				iter.second();
			core_log_info("ObjectPoolInfo End");
		}
	};


#define INIT_OBJECT_SIZE 16
	template<class T>
	class CObjectPool : public CSingleton<CObjectPool<T>>
	{
		using List = std::list<T*>;
		using Iterator = typename std::list<T*>::iterator;

	public:
		const static Iterator NullIter;

		CObjectPool() :_useCount(0), _freeCount(0) {
			CObjectPoolMonitor::monitorPool(typeid(T).name(), [this]() { this->printInfo(); });
		}

		virtual~CObjectPool() {
			auto iter = _freeObjects.begin();
			while (iter != _freeObjects.end())
			{
				delete* iter;
				_freeObjects.erase(iter++);
			}
		}

		template<class ...Args>std::shared_ptr<T> create(Args ...args)
		{
			while (_freeObjects.empty())
				assignObjs(INIT_OBJECT_SIZE);
			T* ptr = _freeObjects.front();
			_freeObjects.pop_front();
			ptr->setOjectorIter(_usingOjects.insert(_usingOjects.end(), ptr));
			ptr->onAwake(std::forward<Args>(args)...);
			++_useCount;
			--_freeCount;
			return std::shared_ptr<T>(ptr, [this](T* ptr) { this->recycle(ptr); });
		}

		void printInfo()
		{
			//cout << typeid(T).name() << " use:" << _useCount << " free:" << _freeCount << endl;
			core_log_info(typeid(T).name(), "user:", _useCount, "free:", _freeCount);
		}

	private:
		List _freeObjects;
		List _usingOjects;
		int32 _useCount;
		int32 _freeCount;

		void recycle(T* ptr) {
			auto iter = ptr->getObjectorIter();
			if (ptr && iter != _usingOjects.end()) {
				ptr->onRecycle();
				_usingOjects.erase(iter);
				ptr->setOjectorIter(NullIter);
				_freeObjects.push_back(ptr);
				++_freeCount;
				--_useCount;
			}
		}

		void assignObjs(int32 amount) {
			for (int32 i = 0; i < amount; ++i, ++_freeCount)
				_freeObjects.push_back(new T());
		}
	};

	template<class T>
	const typename CObjectPool<T>::Iterator CObjectPool<T>::NullIter = CObjectPool<T>::Iterator();


	template<class T>
	class CPoolObject
	{
		using Iterator = typename std::list<T*>::iterator;
		Iterator _poolIter;
	public:
		CPoolObject() :_poolIter(CObjectPool<T>::NullIter) {}

		void setOjectorIter(const Iterator& iter) {
			_poolIter = iter;
		}

		Iterator getObjectorIter() const {
			return _poolIter;
		}
	};

}