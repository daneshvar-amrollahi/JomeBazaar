#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "Shop.hpp"

class RandomNumberHandler : public RequestHandler
{
public:
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler
{
private:
  Shop *shop;
public:
  UploadHandler(Shop *_shop) { shop = _shop; }
  Response *callback(Request *);
};

class SignUpHandler : public RequestHandler
{
private:
  Shop *shop;

public:
  SignUpHandler(Shop *_shop) { shop = _shop; }
  Response *callback(Request *);
};

class LogOutHandler : public RequestHandler
{
private:
  Shop *shop;

public:
  LogOutHandler(Shop *_shop) { shop = _shop; }
  Response *callback(Request *);
};

class BuyerHomeHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    BuyerHomeHandler(Shop *_shop) { shop = _shop; }
    Response *callback(Request *);
};

class AddOfferHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    AddOfferHandler(Shop *_shop) { shop = _shop; }
    Response *callback(Request *);
};

class SellerHomeHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    SellerHomeHandler(Shop *_shop) {shop = _shop; }
    Response *callback(Request *);

};

class WalletHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    WalletHandler(Shop *_shop) {shop = _shop; }
    Response *callback(Request *);
};


class ShowDetailHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    ShowDetailHandler(Shop *_shop) {shop = _shop; }
    Response *callback(Request *);
};

class ChargeWalletHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    ChargeWalletHandler(Shop* _shop) {shop = _shop; }
    Response *callback(Request *);
};

class LoginHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    LoginHandler(Shop* _shop) {shop = _shop; }
    Response *callback(Request *);
};

class AddToCartHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    AddToCartHandler(Shop* _shop) {shop = _shop; }
    Response *callback(Request *);
};

class GoToCartHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    GoToCartHandler(Shop* _shop) {shop = _shop; }
    Response *callback(Request *);
};



class SubmitCartHandler: public RequestHandler
{
  private:
    Shop* shop;
  public:
    SubmitCartHandler(Shop* _shop) {shop = _shop; }
    Response *callback(Request *);
};

#endif
