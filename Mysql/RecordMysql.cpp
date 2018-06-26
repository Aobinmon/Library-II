#include"RecordMysql.h"

RecordMysql::RecordMysql(QSqlDatabase& db):Mysql(db){
    gm = new GuestMysql(db);
    bm = new BookMysql(db);
}

std::vector<Record*> RecordMysql::findRecord( QString usertype,QString infotype, QString info,QString userID)//如果是管理员的话，userID就设为-1
{
        std::vector<Record*> recordlist;
        bool ifbookname=false;
         if(usertype=="administrator"){//管理员权限
           if(info == "") query->exec("select * from done_record ORDER BY ID DESC");
           else if(infotype=="ID"||infotype=="state"||infotype=="Type"||infotype=="BookID"||infotype=="GuestID")//int类型
           query->exec("select* from done_record where "+infotype+"="+info);
           else if(infotype=="time")
               query->exec("select* from done_record where "+infotype+"=\""+info+"\";");
           else if(infotype == "BookName"){                                  //书名相同但ID有可能不同
               ifbookname = true;
               std::vector<Book*> books = bm->findBook("Bookname", info);
               for(int i=0; i<books.size(); ++i){
                   QString id = QString::number(books[i]->getID());
                  query->exec("select * from done_record where  BookID=" + id + " order by ID DESC");
                  while(query->next()){
                  int id=query->value(0).toInt();
                  int type=query->value(3).toInt();
                  std::string time=query->value(4).toString().toStdString();
                  int bookid=query->value(1).toInt();
                  int readerid=query->value(2).toInt();
                  int result=query->value(5).toInt();
                 Book *book = bm->findBook("ID", QString::number(bookid)).front();
                 Guest *guest = gm->find_guest("ID", QString::number(readerid)).front();
                 recordlist.push_back(new Record(guest, book, type, id, result, time));
                  }
               }
           }
           else if(infotype == "GuestName"){
                Guest* g = gm->find_guest("Username", info).front();
                query->exec("select * from done_record where GuestID=" + QString::number(g->getID()) + " order by  ID DESC");
            }
         }
            else if(usertype=="guest"){//用户的查询，只能看到readerID=userID的借阅信息
             if(info == "") query->exec("select * from done_record where GuestID=" + userID + " order by ID DESC");
             else if(infotype=="Type"||infotype=="BookID")
                    query->exec("select * from done_record where GuestID="+userID+" and "+infotype+"="+info +" order by ID DESC");
               else if(infotype=="Time")
                    query->exec("select * from done_record where GuestID="+userID+" and "+infotype+"=\""+info+"\" order by ID DESC");
                else if(infotype == "BookName"){
                 ifbookname = true;
                 std::vector<Book*> books = bm->findBook("Bookname", info);
                 for(int i=0; i<books.size(); ++i){
                     QString id = QString::number(books[i]->getID());
                    query->exec("select * from done_record where GuestID=" + userID + " and BookID=" + id + " order by ID DESC");
                    while(query->next()){
                    int id=query->value(0).toInt();
                    int type=query->value(3).toInt();
                    std::string time=query->value(4).toString().toStdString();
                    int bookid=query->value(1).toInt();
                    int readerid=query->value(2).toInt();
                    int result=query->value(5).toInt();
                   Book *book = bm->findBook("ID", QString::number(bookid)).front();
                   Guest *guest = gm->find_guest("ID", QString::number(readerid)).front();
                   recordlist.push_back(new Record(guest, book, type, id, result, time));
                    }
                 }
                }
           }
         if(!ifbookname){
             while(query->next()){
             int id=query->value(0).toInt();
             int type=query->value(3).toInt();
             std::string time=query->value(4).toString().toStdString();
             int bookid=query->value(1).toInt();
             int readerid=query->value(2).toInt();
             int result=query->value(5).toInt();
            Book *book = bm->findBook("ID", QString::number(bookid)).front();
            Guest *guest = gm->find_guest("ID", QString::number(readerid)).front();
            recordlist.push_back(new Record(guest, book, type, id, result, time));
             }
         }
         qDebug() << recordlist.size();
            return recordlist;
}

void RecordMysql::approve_or_refuse(Record *record, int approve){
    int id = record->getID();
    int Bid = record->getBook()->getID();
    int Gid = record->getGuest()->getID();
    int type = record->getType();
    std::string time = record->getTime();
    if(approve == 1){
        query->exec("insert into done_record (ID, BookID, GuestID, Type, Time, Result)"
                   "VALUES"
                   "(" + QString::number(id) + "," +
                   QString::number(Bid) + "," +
                   QString::number(Gid) + "," +
                   QString::number(type) + "," +
                    "NOW(), 0 );");
    }
    else if(approve == 0){
        query->exec("insert into done_record (ID, BookID, GuestID, Type, Time, Result)"
                   "VALUES"
                   "(" + QString::number(id) + "," +
                   QString::number(Bid) + "," +
                   QString::number(Gid) + "," +
                   QString::number(type) + "," +
                   QString::fromStdString(time) + ",1 );");
    }
}
