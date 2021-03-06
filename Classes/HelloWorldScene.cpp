#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //画面の幅を取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //原点を取得
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add the label as a child to this layer

    //画像ファイルを指定してスプライトを作成
    auto sprite = Sprite::create("monkey01.png");

    sprite->setTextureRect(Rect(0,0,100,135));

    // 画像のポジションを設定
    sprite->setPosition(Vec2(sprite->getContentSize().width*3/2+origin.x, visibleSize.height/2+origin.y));

    sprite->setTag(1);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic),3.0);

    return true;
}

void HelloWorld::addFood()
{

	//ハンバーガーのスプライトを作成してレイヤへ追加
	Size winSize = Director::getInstance()->getVisibleSize();

	auto food = Sprite::create("hamburger.png");
	food->setTextureRect(Rect(0,0,36,30));

	int height = rand() % (int)winSize.height;
	food->setPosition(Vec2(winSize.width + food->getContentSize().width/2,height));

	food->setTag(2);
	this->addChild(food);

	//アクションの継続時間
	float duration = 2.0f;
	//アクション作成
	auto move = MoveTo::create(duration,
							Point(food->getContentSize().width*3/2,
									food->getPositionY()));
	//food->runAction(move);

	auto call = CallFuncN::create(this,callfuncN_selector(HelloWorld::spriteMoveFinished));

	food->runAction(Sequence::create(move,call,NULL));

}

void HelloWorld::gameLogic(float dt)
{
	this->addFood();
}

void HelloWorld::spriteMoveFinished(Node* sender)
{
	auto sprite = (cocos2d::Sprite *)sender;

	//ハンバーガーのスプライトを取得し、親レイヤーのremoveChildの第一引数に指定して、削除
	//第二引数をtureに設定すると削除する子で実行中のアクションやコールバックも同時に破棄される。
	bool isCleanUp = true;
	this->removeChild(sprite,isCleanUp);

	//Visibleプロパティで非表示にすることも可能
	//この場合描画処理は行われない
	//sprite->setVisible(false);

	//opacityで透明に
	//こちらの場合描画処理が行われるので↑のVisibleの方を推奨
	//sprite->setOpacity(0);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
