#pragma once
#include <QObject>

 /************************************************************************/
 /*                         智能指针单例基类                             */
 /************************************************************************/
 
 #include <mutex>
 #include <memory>
 
 template <typename T>
 class DSingleton
 {
 public:
 	static std::shared_ptr<T> GetInstance()
 	{
 		if (!m_pSington)
 		{
 			std::lock_guard<std::mutex> gLock(m_Mutex);
 			if (nullptr == m_pSington)
 			{
 				m_pSington = std::make_shared<T>();
 			}
 		}
 		return m_pSington;
 	}
 	static void DesInstance()
 	{
 		if (m_pSington)
 		{
 			m_pSington.reset();
 			m_pSington = nullptr;
 		}
 	}
 public:
 	class GC
 	{
 	public:
 		~GC()
 		{
 			if (m_pSington != nullptr)
 			{
 				DesInstance();
 			}
 		}
 		static GC gc;
 	};
 
 
 private:
 	explicit DSingleton();
 	DSingleton(const DSingleton&) = delete;
 	DSingleton& operator=(const DSingleton&) = delete;
     ~DSingleton() {}
 
 private:
 	static std::shared_ptr<T> m_pSington;
 	static std::mutex m_Mutex;
 };
 template<typename T>
 std::shared_ptr<T> DSingleton<T>::m_pSington = nullptr;
 
 template<typename T>
 std::mutex DSingleton<T>::m_Mutex;
 
 template<typename T>
 std::shared_ptr<T> DSingleton<T>::GC::gc;
