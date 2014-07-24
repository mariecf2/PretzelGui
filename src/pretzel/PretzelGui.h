//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "ScrollPane.h"
#include "PretzelRow.h"

#include "PretzelLabel.h"
#include "PretzelSlider.h"
#include "PretzelSaveLoad.h"
#include "PretzelButton.h"
#include "PretzelToggle.h"
#include "PretzelTextField.h"
#include "PretzelColorPicker.h"

namespace Pretzel{
	class PretzelGui : public ScrollPane {
        
	public:
		PretzelGui(std::string title = "");
		PretzelGui(std::string title, int width, int height);
        ~PretzelGui();
        
		void draw();
		void setSize(ci::Vec2i size);
		void setPos(const ci::Vec2i &pos);
		void minimize(bool doMinimize = true);
		void setVisible(bool visible);
		void toggleVisible();
		bool isVisible();

		void saveSettings(ci::fs::path settingsPath = ci::fs::path());
		void loadSettings(ci::fs::path settingsPath = ci::fs::path());

		// ------------------
		void addLabel(std::string labelText);
		void addSlider(std::string label, float *variable, float min, float max);
		void addSlider(std::string label, int *variable, int min, int max);
        void addSlider(std::string label, ci::Vec2f *variable, ci::Vec2f min, ci::Vec2f max);
        void addSlider(std::string label, ci::Vec3f *variable, ci::Vec3f min, ci::Vec3f max);
        void addSaveLoad();
		void addToggle(std::string label, bool *value);
		void addTextField(std::string label, std::string *variable, bool editable = true);
        
        void addColorPicker(std::string label, ci::Color *color);
        void addColorPicker(std::string label, ci::ColorA *color);
        
		template<typename T, typename Y>
		inline void addButton(std::string labelText, T callback, Y *callbackObject){
			PretzelButton *newButton = new PretzelButton(this, labelText);
			newButton->mConnection = newButton->signalOnPress.connect(std::bind(callback, callbackObject));
            
            mWidgetList.push_back( newButton );
		}

	private:
		void init(std::string title = "");
        void connectSignals();
        void disconnectSignals();
        void onSettingsLoaded();

		// mouse events
		boost::signals2::scoped_connection  mMouseBeganCallBack,
			mMouseDragCallBack,
			mMouseEndCallBack,
			mMouseMovedCallBack,
			mKeyDownCallback;

		virtual void onMouseDown(ci::app::MouseEvent &event);
		virtual void onMouseDragged(ci::app::MouseEvent &event);
		virtual void onMouseUp(ci::app::MouseEvent &event);
		virtual void onMouseMoved(ci::app::MouseEvent &event);
		virtual void onKeyDown(ci::app::KeyEvent &event);
        
        std::vector<BasePretzel*>    mWidgetList;

		PretzelLabel	*mDefaultLabel;
		bool			bVisible;
		bool			bDragging;
		bool			bResizing;

		ci::Vec2f		mMouseOffset;
		ci::Vec2f		mResizeStartSize;

		ci::Rectf		mResizeRect;

		double			mLastClickTime;
		bool			bDrawMinimized;
        bool            bChangedCursor;
	};
}