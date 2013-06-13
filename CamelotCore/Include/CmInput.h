#pragma once

#include "CmPrerequisites.h"
#include "CmModule.h"
#include "CmRect.h"
#include "CmInputHandler.h"

namespace CamelotFramework
{
	class CM_EXPORT Input : public Module<Input>
	{
	public:
		Input();
		~Input();

		boost::signal<void(const KeyEvent&)> onKeyDown;
		boost::signal<void(const KeyEvent&)> onKeyUp;

		boost::signal<void(const MouseEvent&)> onMouseMoved;
		boost::signal<void(const MouseEvent&, MouseButton)> onMouseDown;
		boost::signal<void(const MouseEvent&, MouseButton)> onMouseUp;

		void registerInputHandler(InputHandlerPtr inputHandler);

		/**
		 * @brief	Called every frame. Dispatches any callbacks resulting from input by the user. Should only be called by Application.
		 */
		void update();

		/**
		 * @brief	Captures any input between this and last call to capture. MUST be called from the render
		 * 			thread, because thats the thread that owns the input window.
		 */
		void capture();

		/**
		 * @brief	Should be called any time window in focus changes. Should only be called by Application.
		 */
		void inputWindowChanged(const RenderWindow& win);

		/**
		 * @brief	Returns smoothed mouse/joystick input in the horizontal axis.
		 *
		 * @return	The horizontal axis value ranging [-1.0f, 1.0f].
		 */
		float getHorizontalAxis() const;

		/**
		 * @brief	Returns smoothed mouse/joystick input in the vertical axis.
		 *
		 * @return	The vertical axis value ranging [-1.0f, 1.0f].
		 */
		float getVerticalAxis() const;

		bool isButtonDown(MouseButton button) const;
		bool isKeyDown(KeyCode keyCode) const;

	private:
		InputHandlerPtr mInputHandler;

		float mSmoothHorizontalAxis;
		float mSmoothVerticalAxis;

		float* mHorizontalHistoryBuffer;
		float* mVerticalHistoryBuffer;
		float* mTimesHistoryBuffer;
		int	mCurrentBufferIdx;

		Int2 mMouseLastRel;

		bool mMouseButtonState[MB_Count];
		bool mKeyState[KC_Count];

		void keyDown(const KeyEvent& event);
		void keyUp(const KeyEvent& event);

		void mouseMoved(const MouseEvent& event);
		void mouseDown(const MouseEvent& event, MouseButton buttonID);
		void mouseUp(const MouseEvent& event, MouseButton buttonID);

		/**
		 * @brief	Updates the input values that need smoothing.
		 */
		void updateSmoothInput();

		/************************************************************************/
		/* 								STATICS		                      		*/
		/************************************************************************/
		static const int HISTORY_BUFFER_SIZE; // Size of buffer used for input smoothing
		static const float WEIGHT_MODIFIER;
	};

	CM_EXPORT Input& gInput();
}