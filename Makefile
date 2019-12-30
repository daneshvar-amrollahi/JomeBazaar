CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) a.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Shop.o: Shop.cpp
	$(CC) $(CF) -c Shop.cpp -o $(BUILD_DIR)/Shop.o

$(BUILD_DIR)/User.o: User.cpp
	$(CC) $(CF) -c User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Admin.o: Admin.cpp
	$(CC) $(CF) -c Admin.cpp -o $(BUILD_DIR)/Admin.o

$(BUILD_DIR)/Seller.o: Seller.cpp
	$(CC) $(CF) -c Seller.cpp -o $(BUILD_DIR)/Seller.o

$(BUILD_DIR)/Buyer.o: Buyer.cpp
	$(CC) $(CF) -c Buyer.cpp -o $(BUILD_DIR)/Buyer.o

$(BUILD_DIR)/Product.o: Product.cpp
	$(CC) $(CF) -c Product.cpp -o $(BUILD_DIR)/Product.o

$(BUILD_DIR)/Mobile.o: Mobile.cpp
	$(CC) $(CF) -c Mobile.cpp -o $(BUILD_DIR)/Mobile.o

$(BUILD_DIR)/Car.o: Car.cpp
	$(CC) $(CF) -c Car.cpp -o $(BUILD_DIR)/Car.o

$(BUILD_DIR)/Tv.o: Tv.cpp
	$(CC) $(CF) -c Tv.cpp -o $(BUILD_DIR)/Tv.o

$(BUILD_DIR)/Offer.o: Offer.cpp
	$(CC) $(CF) -c Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/Discount.o: Discount.cpp
	$(CC) $(CF) -c Discount.cpp -o $(BUILD_DIR)/Discount.o

$(BUILD_DIR)/Order.o: Order.cpp
	$(CC) $(CF) -c Order.cpp -o $(BUILD_DIR)/Order.o

a.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/Shop.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Mobile.o $(BUILD_DIR)/Car.o $(BUILD_DIR)Tv.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Discount.o $(BUILD_DIR)/Order.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/Shop.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Mobile.o $(BUILD_DIR)/Car.o $(BUILD_DIR)/Tv.o $(BUILD_DIR)/Offer.cpp $(BUILD_DIR)/Discount.cpp $(BUILD_DIR)/Order.cpp

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null