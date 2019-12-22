a.out: main.o Shop.o User.o Admin.o Seller.o Buyer.o Product.o Mobile.o Car.o Tv.o Offer.o Discount.o Order.o
	g++ -std=c++11 main.o Shop.o User.o Admin.o Seller.o Buyer.o Product.o Mobile.o Car.o Tv.o Offer.cpp Discount.cpp Order.cpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Shop.o: Shop.cpp
	g++ -std=c++11 -c Shop.cpp

User.o: User.cpp
	g++ -std=c++11 -c User.cpp

Admin.o: Admin.cpp
	g++ -std=c++11 -c Admin.cpp

Seller.o: Seller.cpp
	g++ -std=c++11 -c Seller.cpp

Buyer.o: Buyer.cpp
	g++ -std=c++11 -c Buyer.cpp

Product.o: Product.cpp
	g++ -std=c++11 -c Product.cpp

Mobile.o: Mobile.cpp
	g++ -std=c++11 -c Mobile.cpp

Car.o: Car.cpp
	g++ -std=c++11 -c Car.cpp

Tv.o: Tv.cpp
	g++ -std=c++11 -c Tv.cpp

Offer.o: Offer.cpp
	g++ -std=c++11 -c Offer.cpp

Discount.o: Discount.cpp
	g++ -std=c++11 -c Discount.cpp

Order.o: Order.cpp
	g++ -std=c++11 -c Order.cpp