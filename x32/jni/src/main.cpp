#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <cocos2d.h>
#include <gd.h>
#include "libs/hook/inlineHook.h"

// import cocos
using namespace cocos2d;

class Links : public cocos2d::CCLayer 
{
public:
    void Creditos( cocos2d::CCObject* selector) 
    {
        auto app = cocos2d::CCApplication::sharedApplication( );
        auto url = ("http://ps.fhgdps.com/GDPSEditor22/os.html");

        app->openURL(url);
    }
};
namespace h_menuLayer {

    // define the layer
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
        auto label22 = CCLabelBMFont::create("Version 2.2.0.5", "chatFont.fnt");
        label22->setPosition(CCPoint(dir->getScreenRight() - 55, dir->getScreenTop() - 10));
        label22->setAnchorPoint({ 0, 0 });
        label22->setScale(.5);
        self->addChild(label22);


        // credits button **new addon**
        auto creditos = CCSprite::createWithSpriteFrameName("communityCreditsBtn_001.png");

        auto creditosbut = CCMenuItemSpriteExtra::create(
        creditos,
        creditos,
        self,
        menu_selector(Links::Creditos));
        
        auto creditosmen = CCMenu::create();

        creditosmen->setPosition({5, 90});
        creditosmen->addChild(creditosbut);
        creditosmen->setScale(.7);
        self->addChild(creditosmen, 100);

        //the other button XD
        auto showfps = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
        showfps->setScale(1);
        auto btn2 = CCMenuItemSpriteExtra::create(showfps, showfps, self, menu_selector(VideoOptionsLayer::onAdvanced));
        menu2->addChild(btn2);
        menu2->setPosition(CCPoint(dir->getScreenRight() - 43, dir->getScreenTop() - 35));
        self->addChild(menu2, 100);

        return ret;
    }
}

/*
namespace h_LoadingLayer {
    
    void(*o_enit)(CCLayer*);
    void* enit(CCLayer* self) {
        
        auto ret = o_enit(self);
        
        // define game manager

        auto gm = GameManager::sharedState();
		
        gm->setGameVariable("0109", false); // level info thing
        gm->setGameVariable( "0053", false ); // more games thing
        
        gm->setHasRatingPower( 1 ); // fix mod button thing
        
        return ret;
		}
}
*/

namespace MoreOptionsLayerHook
{
    void* (*MoreOptionsLayer_init)(cocos2d::CCLayer*);
    void* MoreOptionsLayer_initHook(cocos2d::CCLayer* self) {
	auto ret = MoreOptionsLayer_init(self);
	
	auto moreOptionsLayer =  MoreOptionsLayer::create();
	    
        moreOptionsLayer->addToggle("Enable information for levels", "0109", "when is enabled you can see all level info from robtop");
        moreOptionsLayer->addToggle("Enable FPS Counter", "0115", "When enabled, your current FPS will be showed while in the menus and playing levels");

        return ret;
    }
}
__attribute__((constructor))
void fdml_init() {
    hook("_ZN9MenuLayer4initEv", h_menuLayer, init, o_init);
	//hook("_ZN12LoadingLayer16getLoadingStringEv", h_LoadingLayer, enit, o_enit);
	hook("_ZN16MoreOptionsLayer4initEv", MoreOptionsLayerHook, MoreOptionsLayer_initHook, MoreOptionsLayer_init);
    inlineHookAll();
}

