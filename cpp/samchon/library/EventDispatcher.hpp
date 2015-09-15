#pragma once


#include <memory>

#include <samchon/library/CriticalSet.hpp>
#include <samchon/library/CriticalMap.hpp>

namespace samchon
{
	namespace library
	{
		class Event;
		class ErrorEvent;
		class ProgressEvent;

		/**
		 * @brief Abstract class for dispatching Event
		 *
		 * @details
		 * <p> EventDispatcher is the base class for all classes that dispatch events. </p>
		 * 
		 * @note 
		 * <p> EventDispatcher is a candidate to be depreciated. </p>
		 * <p> Since C++11, calling member method of a class by a new thread passing by static 
		 * method and using void pointer are recommeded to avoid. As the reason, using <i>std::thread</i> 
		 * and <i>std::bind will</i> be better. </p>
		 *
		 *	\li std::thread: http://www.cplusplus.com/reference/thread/thread/
		 *	\li std::bind: http://www.cplusplus.com/reference/functional/bind/
		 *
		 * @author Jeongho Nam
		 */
		class  EventDispatcher
		{
		private:
			//EVENT-LISTENER CONTAINERS
			/**
			 * @brief A container storing listeners
			 */
			CriticalMap<int, std::shared_ptr<CriticalSet<void(*)(std::shared_ptr<Event>)>>> eventSetMap; //EVENT

		public:
			//CONSTRUCTORS
			/**
			 * @brief Default Constructor
			 */
			EventDispatcher();

			/**
			 * @brief Copy Constructor
			 *
			 * @details
			 * Copying an EventDispatcher instance does not copy the event listeners attached to it. 
			 * (If your newly created node needs an event listener, you must attach the listener after creating the node.)
			 *
			 * @param eventDispatcher The object to copy
			 */
			EventDispatcher(const EventDispatcher &eventDispatcher);

			/**
			 * @brief Move Constructor
			 *
			 * @param eventDispatcher The object to move
			 */
			EventDispatcher(EventDispatcher &&eventDispatcher);
			virtual ~EventDispatcher() = default;

			/* ----------------------------------------------------------
				ADD-REMOVE EVENT LISTENERS
			---------------------------------------------------------- */
			/**
			 * @brief Register an event listener
			 *
			 * @details 
			 * Registers an event listener object with an EventDispatcher object 
			 * so that the listener receives notification of an event.
			 *
			 * @warning Copying an EventDispatcher instance does not copy the event listeners attached to it.
			 *			(If your newly created node needs an event listener, you must attach the listener after creating the node.) 
			 *			However, if you move an EventDispatcher instance, the event listeners attached to it move along with it.
			 *
			 * @warning If you no longer need an event listener, remove it by calling removeEventListener,
			 *			or EventDispatcher already try to send events to the no longer needed listener and
			 *			it can cause some confliction.
			 *
			 * @param type The type of event.
			 * @param listener The listener function processes the event.
			 */
			virtual void addEventListener(int, void(*listener)(std::shared_ptr<Event>));
			
			/**
			 * @brief Remove a registered event listener
			 *
			 * @details
			 * Removes a listener from the EventDispatcher object. 
			 * If there is no matching listener registered with the EventDispatcher object, a call to this method has no effect
			 *
			 * @param type The type of event.
			 * @param listener The listener function to remove.
			 */
			virtual void removeEventListener(int, void(*listener)(std::shared_ptr<Event>));
			
		protected:
			/* ----------------------------------------------------------
				DISPATCH EVENT
			---------------------------------------------------------- */
			//SEND EVENT
			/**
			 * @brief Dispatches an event to all listeners
			 *
			 * @details
			 * Dispatches an event into the event flow in the background.
			 * The Event::source is the EventDispatcher object upon which the dispatchEvent
			 *
			 * @param event The Event object that is dispatched into the event flow.
			 * @return Whether there's some listener to listen the event
			 */
			auto dispatchEvent(std::shared_ptr<Event>) -> bool;

			/**
			 * @brief Convenient method of dispatching a progress event
			 *
			 * @details
			 * Dispatches a progress event into the event flow in the background
			 * The Event::source is the EventDispatcher object upon with the dispatchProgressEvent
			 *
			 * @param x The number of current progress
			 * @param size The number of total progress
			 * @return Whether there's some listener to listen the progress event
			 *
			 * @see ProgressEvent
			 * @see EventDispatcher::dispatchEvent
			 */
			auto dispatchProgressEvent(double x, double size) -> bool;
		};
	};
};