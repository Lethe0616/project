#include "order_system.hpp"

int main()
{
MYSQL *mysql = _order_sys::MysqlInit();
if(mysql == NULL){
return -1;
}

_order_sys::DishTable dish_tb(mysql);
_order_sys::OrderTable order_tb(mysql);

/*�����Ʒ����
Json::Value dish;
dish["name"] = "�Ǵ�����";
dish["price"] = 3900;
dish_tb.Insert(dish);
*/

/*��ѯ������Ʒ��Ϣ
Json::Value dish1;
Json::StyledWriter writer;
dish_tb.SelectOne(4, &dish1);
std::cout << "dish:" << writer.write(dish1);
*/

/*��ѯ�����Ʒ��Ϣ
Json::Value dish2;
Json::StyledWriter writer2;
dish_tb.SelectOne(4, &dish2);
std::cout << "dish:" << writer.write(dish2);
*/


/*���²�Ʒ��Ϣ
Json::Value dish3;
dish3["id"] = 4;
dish3["name"] = "��������";
dish3["price"] = 4500;
dish_tb.Update(dish3);
*/

/*ɾ����Ʒ��Ϣ
dish_tb.Delect(5);
*/

Json::Value order;
Json::StyledWriter writer;

/*���붩����Ϣ
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

/*ɾ������
order_tb.Delete(1);
*/

_order_sys::MysqlDestory(mysql);
return 0;
}



