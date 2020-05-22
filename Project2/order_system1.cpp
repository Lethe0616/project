#include "order_system.hpp"

int main()
{
MYSQL *mysql = _order_sys::MysqlInit();
if(mysql == NULL){
return -1;
}

_order_sys::DishTable dish_tb(mysql);
_order_sys::OrderTable order_tb(mysql);

/*插入菜品测试
Json::Value dish;
dish["name"] = "糖醋丸子";
dish["price"] = 3900;
dish_tb.Insert(dish);
*/

/*查询单个菜品信息
Json::Value dish1;
Json::StyledWriter writer;
dish_tb.SelectOne(4, &dish1);
std::cout << "dish:" << writer.write(dish1);
*/

/*查询多个菜品信息
Json::Value dish2;
Json::StyledWriter writer2;
dish_tb.SelectOne(4, &dish2);
std::cout << "dish:" << writer.write(dish2);
*/


/*更新菜品信息
Json::Value dish3;
dish3["id"] = 4;
dish3["name"] = "西湖醋鱼";
dish3["price"] = 4500;
dish_tb.Update(dish3);
*/

/*删除菜品信息
dish_tb.Delect(5);
*/

Json::Value order;
Json::StyledWriter writer;

/*插入订单信息
order["table_id"] = 5;
order["dishes"].append(4);
order["dishes"].append(6);
order["status"] = 0;
order_tb.Insert(order);
*/

/*
Json::Value order1;
order_tb.SelectOne(1, &order1);
std::cout << "order:" << writer.write(order1);
*/

/*
order_tb.SelcetAll(&order);
std::cout << "order:" << writer.write(order);
*/

/*
order["id"] = 1;
order["table_id"] = 3;
order["dishes"].append(4);
order["status"] = 0;
order_tb.Update(order);
*/

/*删除订单
order_tb.Delete(1);
*/

_order_sys::MysqlDestory(mysql);
return 0;
}



