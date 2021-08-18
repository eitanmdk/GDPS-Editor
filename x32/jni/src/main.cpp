#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <cocos2d.h>
#include <gd.h>
#include "libs/hook/inlineHook.h"

using namespace cocos2d;

namespace h_MenuLayer {
    
    void* (*o_init)(CCLayer*);
    void* init(CCLayer* self) {
        auto ret = o_init(self);
        
        
        auto dir = CCDirector::sharedDirector();

        auto menu = CCMenu::create();
        auto menu2 = CCMenu::create();
        
        // Created Lvls
        auto createdlvls = CCSprite::createWithSpriteFrameName("GJ_createBtn_001.png");
        
        createdlvls->setScale(.7);
        
        auto btn = CCMenuItemSpriteExtra::create(createdlvls, createdlvls, self, menu_selector(CreatorLayer::onMyLevels));
        
        menu->addChild(btn);
        menu->setPosition(CCPoint(dir->getScreenRight() - 43, dir->getScreenBottom() + 43));
        self->addChild(menu, 100);

        // Version txt
        auto label22 = CCLabelBMFont::create("Version 2.2.0.4 Beta", "chatFont.fnt");
        
        label22->setPosition(CCPoint(dir->getScreenLeft() + 2, dir->getScreenTop() - 10));
        label22->setAnchorPoint({ 0, 0 });
        label22->setScale(.5);
        
        self->addChild(label22);
        
        return ret;
    }
}


namespace h_MoreOptionsLayer {
// addtoggle def
int addToggle(const char* display, const char* key, const char* extraInfo);
    
void* (*o_anit)(CCLayer*);
void* anit(CCLayer* self) {

     auto ret = o_anit(self);
    
     self->addToggle("Enable information for levels", "0109", "when is enabled you can see all level info from robtop");
     self->addToggle("Enable FPS Counter", "0116", "When enabled, your current FPS will be showed while in the menus and playing levels");
    
     return ret;
    
   }
}

namespace h_LoadingLayer {
    
    void(*o_init)(CCLayer*);
    void* init(CCLayer* self) {
        
        auto gm = GameManager::sharedState();
        
        gm->setGameVariable("0115", false); // FPS label thing
        gm->setGameVariable("0109", false); // level info thing
        gm->setGameVariable( "0053", false ); // more games thing
        
        gm->setHasRatingPower( 1 ); // fix mod button thing
        
        return AY_OBFUSCATE("Welcome to GDPS Editor 2.2!");
    }
}
__attribute__((constructor))
void fdml_init() {
    hook("_ZN9MenuLayer4initEv", h_MenuLayer, init, o_init);
    hook("_ZN16MoreOptionsLayer4initEv", h_MoreOptionsLayer, anit, o_anit);
    hook("_ZN12LoadingLayer16getLoadingStringEv", h_LoadingLayer, init, o_init);
    inlineHookAll();
}
