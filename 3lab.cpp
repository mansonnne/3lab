#include <iostream>
#include <string>
#include <vector>

// Фабричный метод
class Product {
public:
    virtual void produce() = 0;
    virtual ~Product() {}
};

class ConcreteProductA : public Product {
public:
    void produce() override {
        std::cout << "Производим продукт типа A\n";
    }
};

class ConcreteProductB : public Product {
public:
    void produce() override {
        std::cout << "Производим продукт типа B\n";
    }
};

class ProductFactory {
public:
    virtual Product* createProduct() = 0;
    virtual ~ProductFactory() {}
};

class ConcreteProductAFactory : public ProductFactory {
public:
    Product* createProduct() override {
        return new ConcreteProductA();
    }
};

class ConcreteProductBFactory : public ProductFactory {
public:
    Product* createProduct() override {
        return new ConcreteProductB();
    }
};

// Абстрактная фабрика
class ProductionFactory {
public:
    virtual Product* createProduct() = 0;
    virtual ~ProductionFactory() {}
};

class ConcreteProductionFactory : public ProductionFactory {
public:
    Product* createProduct() override {
        return new ConcreteProductA();
    }
};

// Одиночка
class ProductionManager {
private:
    static ProductionManager* instance;
    ProductionManager() {}
public:
    static ProductionManager* getInstance() {
        if (!instance) {
            instance = new ProductionManager();
        }
        return instance;
    }
    void produce(ProductFactory* factory) {
        Product* product = factory->createProduct();
        product->produce();
        delete product;
    }
};

ProductionManager* ProductionManager::instance = nullptr;

// Строитель
class ProductBuilder {
protected:
    Product* product;
public:
    ProductBuilder() : product(nullptr) {}
    virtual ~ProductBuilder() {}
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual Product* getResult() = 0;
};

class ConcreteProductBuilder : public ProductBuilder {
public:
    void buildPartA() override {
        // Создание части A продукта
    }
    void buildPartB() override {
        // Создание части B продукта
    }
    Product* getResult() override {
        // Возвращение готового продукта
        return product;
    }
};

int main() {
    // Фабричный метод
    ProductFactory* factoryA = new ConcreteProductAFactory();
    ProductionManager::getInstance()->produce(factoryA);

    ProductFactory* factoryB = new ConcreteProductBFactory();
    ProductionManager::getInstance()->produce(factoryB);

    // Абстрактная фабрика
    ProductionFactory* productionFactory = new ConcreteProductionFactory();
    ProductionManager::getInstance()->produce(dynamic_cast<ProductFactory*>(productionFactory));

    // Строитель
    ProductBuilder* builder = new ConcreteProductBuilder();
    builder->buildPartA();
    builder->buildPartB();
    Product* product = builder->getResult();

    delete factoryA;
    delete factoryB;
    delete productionFactory;
    delete builder;
    delete product;

    return 0;
}
