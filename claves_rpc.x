struct Coord {
   int x ;
   int y ;
} ;

struct ret_get_value{
   int status;
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct Coord value3;
};
struct arg_send_values{
   int key;
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct Coord value3;
};

program CLAVESRPC{

   version CLAVESRPC{
      int destroy(void)=1;

      int create(void)=0;

      int set_value(struct arg_send_values a1)=2;


      struct ret_get_value get_value( int key )=3;

      int modify_value(struct arg_send_values a2)=4;

      int delete_key(int key)=5;

      int exist(int key)=6;
   }=1;

}=100456709;