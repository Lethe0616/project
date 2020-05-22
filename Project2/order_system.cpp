#include "order_system.hpp"
#include "httplib.h"

_order_sys::DishTable *dish_table;
_order_sys::OrderTable *dish_table;

void InsertDish(const httplib::Requst &req,httplib::Response &rsp){

Json::Value dish_val;
Json::Reader reader;
bool ret = reader.parse(req.body,dish_val);
if(ret==false){
	std::cout<<"InsertDish parse json data failed!!\n";
	rsp.status=400;
}
ret=dish_table->Insert(dish_val);
if(ret==false){
	rsp.status=500;
	return;
}
rsp.status=200;
return ;	
}

void DeleteDish(const httplib::Requst &req,httplib::Response &rsp){
int dish_id=std::stoi(req.matches[1]);

bool ret=dish_table->Delete(dish_id);
if(ret=false){
	std::cout<<"DeleteDish delete dish from db failed!!\n";
	rsp.status=500;
}
rsp.status=200;
return ;	
}

void UpdateDish(const httplib::Requst &req,httplib::Response &rsp){
Json::Value dish_val;
Json::Reader reader;
bool ret = reader.parse(req.body,dish_val);
if(ret==false){
	rsp.status=400;
}

ret=dish_table->Update(dish_val);
if(ret==false){
	rsp.status=500;
	return;
}
rsp.status=200;
return ;	
}

void SelectOneDish(const httplib::Requst &req,httplib::Response &rsp){
int dish_id=std::stoi(req.matches[1]);
Json::Value dish_val;
bool ret=dish_table->SelectOne(dish_id,&dish_val);
if(ret==false){
	rsp.status=500;
	return;
}

Json::FastWriter writer;
std::string body=write.write(dish_val);

rsp.set_content(body.c_str(),body.size(),"application/json");
rsp.status=200;
return ;	
}

void SelectAllDish(const httplib::Requst &req,httplib::Response &rsp){
Json::Value dish_val;
bool ret=dish_table->SelectAll(&dish_val);
if(ret==false){
	rsp.status=500;
	return;
}

std::string body;
Json::FastWriter writer;
body =writer.write(dishes_val);

rsp.set_content(body.c_str(),body.size(),"application/json");
rsp.status=200;
return ;	
}

void InsertOrder(const httplib::Requst &req,httplib::Response &rsp){
Json::Value order_val;
Json::Reader reader;
bool ret = reader.parse(req.body,order_val);
if(ret==false){
	std::cout<<"InsertOrder parse json failed!!\n";
	rsp.status=400;
	return;
}
ret=order_table->Insert(order_val);
if(ret==false){
	std::cout<<"InsertOrder insert data to db failed!!\n";
	rsp.status=500;
	return;
}
rsp.status=200;
return ;	
}

void DeleteOrder(const httplib::Requst &req,httplib::Response &rsp){
int order_id=std::stoi(req.matches[1]);

bool ret=order_table->Delete(order_id);
if(ret=false){
	std::cout<<"DeleteOrder delete order failed!!\n";
	rsp.status=500;
	return ;
}
rsp.status=200;
return ;	
}

void UpdateOrder(const httplib::Requst &req,httplib::Response &rsp){
Json::Value order_val;
Json::Reader reader;
bool ret = reader.parse(req.body,order_val);
if(ret==false){
	std::cout<<"UpdateOrder parse json failed!!\n";
	rsp.status=400;
	return ;
}

ret=order_table->Update(order_val);
if(ret==false){
	std::cout<<"UpdateOrder update data to db failed!!\n";
	return ;
}
rsp.status=200;
return ;	
}

void SelectOneOrder(const httplib::Requst &req,httplib::Response &rsp){
int order_id=std::stoi(req.matches[1]);
Json::Value order_val;
bool ret=order_table->SelectOne(order_id,&order_val);
if(ret==false){
	std::cout<<"SelectOneOrder get order info from db failed\n";
	return ;
}

Json::FastWriter writer;
std::string body=write.write(order_val);

rsp.set_content(body.c_str(),body.size(),"application/json");
rsp.status=200;
return ;	
}

void SelectAllOrder(const httplib::Requst &req,httplib::Response &rsp){
int order_id=std::stoi(req.matches[1]);
Json::Value order_val;
bool ret=order_table->SelectAll(order_id,&order_val);
if(ret==false){
	std::cout<<"SelectAllOrder get order info from db failed\n";
	return ;
}

Json::FastWriter writer;
std::string body=write.write(order_val);

rsp.set_content(body.c_str(),body.size(),"application/json");
rsp.status=200;
return ;	
}

#define WWWROOT "./wwwroot/"
int main()
{
MYSQL *mysql = _order_sys::MysqlInit();
dish_table =new _order_sys::DishTable(mysql);
order_table =new _order_sys::DishTable(mysql);

httplib::Server server;
server.set_base_dir(WWWROOT) 
//插入菜品请求
server.Post("/dish",InsertDish);
//删除菜品请求
server.Delete("/dish",DeleteDish);
//更新菜品请求
server.Put("/dish",UpdateDish);
//查询单个菜品请求 
server.Get("/dish/num",SelectOneDish);
//查询所有菜品请求 
server.Get("/dish",SelectAllDish);
//订单信息的增删改查
server.Post("/order",InsertOrder);
server.Delete("/order",InsertOrder);
server.Put("/order",UpdateOrder);
server.Get("/order",SelectOrder);

server.listen("0.0.0.0",9000);
_order_sys::MysqlDestory(mysql);
return 0;
}
