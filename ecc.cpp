
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include<bitset>
#include<cstring>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

struct Point 
{
	mpz_t x;
	mpz_t y;
};

struct Dummy
{
    mpz_t temp;
};

string binarystring(unsigned long n)
{
    char binaryarray[33];
    unsigned index = 32;
    binaryarray[index] = '\0';
    do
    {
        binaryarray[--index] = '0' + (n & 1);
    } while (n >>= 1);

    return string(binaryarray + index);
}


int shanks(mpz_t a, const mpz_t x, const mpz_t prime) 
{
    mpz_t temp, inverse, y;
    unsigned int i, m;

      if(mpz_divisible_p(x, prime)) 
      {         
          mpz_set_ui(a, 0);               
          return 1;                       
      }                                   

      if(mpz_legendre(x, prime) != 1)        
      { 
           return 0;   
      }   
      
      if(mpz_tstbit(prime, 1) == 1) 
      {        
         mpz_set(a, prime);
          mpz_add_ui(a, a, 1);
          mpz_fdiv_q_2exp(a, a, 2);
          mpz_powm(a, x, a, prime);           
          return 1;
      }

      mpz_init(y);
      mpz_init(temp);
      mpz_init(inverse);

      mpz_set(a, prime);
      mpz_sub_ui(a, a, 1);               
      m = 0;                             
      
      while(mpz_tstbit(a, m) == 0) 
      {m++;}
      
      mpz_fdiv_q_2exp(a, a, m);           
      mpz_set_ui(temp, 2);                   
      
      while(mpz_legendre(temp, prime) != -1)     
          {mpz_add_ui(temp, temp, 1);}          
      
      mpz_powm(temp, temp, a, prime);               
      mpz_add_ui(a, a, 1);
      mpz_fdiv_q_2exp(a, a, 1);           
      mpz_powm(a, x, a, prime);               
      mpz_invert(inverse, x, prime);
      
      for(;;) 
      {
            mpz_powm_ui(y, a, 2, prime);     
            mpz_mul(y, y, inverse);
            mpz_mod(y, y, prime);            
            i = 0;
            while(mpz_cmp_ui(y, 1) != 0) 
            {
                i++;
                mpz_powm_ui(y, y, 2, prime);  
            }
            
            if(i == 0)
            {                    
                
                mpz_clear(temp); mpz_clear(inverse); mpz_clear(y);
                return 1;
            }
            
            if(m-i == 1)
            {                  
                mpz_mul(a, a, temp);     
            }
            
            else
            {
                mpz_powm_ui(y, temp, 1 << (m-i-1), prime);
                mpz_mul(a, a, y);
            }
            mpz_mod(a, a, prime);         
        }

      mpz_clear(temp); mpz_clear(inverse); mpz_clear(y);
      return 0;
}


int calculate(mpz_t x,mpz_t p)
{
    struct Dummy M;
    mpz_t x_3;
    mpz_t five_x;
    mpz_t eight;
    mpz_init(x_3);
    mpz_init(five_x);
    mpz_init(eight);
    mpz_pow_ui(x_3,x,3);
    mpz_mul_ui(five_x,x,5);
    mpz_neg(five_x,five_x);
    mpz_set_ui(eight,8);
    mpz_add(x_3,x_3,five_x);
    mpz_add(x_3,x_3,eight);

    mpz_mod(x_3,x_3,p);

    // gmp_printf(" %Zd hah ",x_3);

    mpz_init(M.temp);
    mpz_set(M.temp,x_3);

    mpz_t a_1;
    mpz_init(a_1);
    mpz_set_ui(a_1,6);
    Dummy A;
    mpz_set(a_1,x);

    // after plugging the values

    mpz_t q;
    mpz_init(q);
    
    int final_result = shanks(q,M.temp,p);
    
    if( final_result == 1)
    {
        gmp_printf("Point exists, y is %Zd",q);
        return 0;
    }

    else if (final_result == 0 )
    {
        gmp_printf("Point doesnt exist",q);
        return 0;

    }
    else
    {
        gmp_printf("Point doesnt exist",q);
        return 0;
    }


    return 0;
}


Point Negate( Point P, mpz_t p, mpz_t a, mpz_t b)
{

    mpz_neg(P.y,P.y);
    mpz_mod(P.y,P.y,p);

    return P;

}



Point Addition( Point P, Point Q, mpz_t p, mpz_t a, mpz_t b)
{
    int flag = 0;
        
    if(mpz_cmp_si(P.x,-1)==0  &&  mpz_cmp_si(P.y,-1)==0  &&  mpz_cmp_si(Q.x,-1)==0  &&  mpz_cmp_si(Q.y,-1)==0 )
    {

        Point R;
        mpz_init(R.x);
        mpz_init(R.y);
        //std::printf("Case 1 %s","");
        mpz_set_si(R.x,-1);
        mpz_set_si(R.y,-1);
        return R;
    } //case 1


    else if(  mpz_cmp_si(P.x,-1)==0 && mpz_cmp_si(P.y,-1)==0  )
    {
        Point R;
        mpz_init(R.x);
        mpz_init(R.y);
        //std::printf("Case 2a: %s","");
        mpz_set(R.x,Q.x);
        mpz_set(R.y,Q.y);

        return R;
    } //case 2 a 


    else if (  mpz_cmp_si(Q.x,-1)==0 && mpz_cmp_si(Q.y,-1)==0  )
    {
        Point R;
        mpz_init(R.x);
        mpz_init(R.y);
        //std::printf("Case 2b: %s","");
        mpz_set(R.x,P.x);
        mpz_set(R.y,P.y);

        return R;
    } //case 2 b




    else if( mpz_cmp(P.x,Q.x)==0 && mpz_cmp(P.y,Q.y)==0)
    {

        mpz_t x_r, y_r,x_p,y_p,m,x_sq,m_sq,prod,diff;

        struct Point R;
        mpz_init(R.x);
        mpz_init(R.y);


        mpz_init(x_r);
        mpz_init(y_r);
        mpz_init(x_p);
        mpz_init(y_p);
        mpz_init(m);
        mpz_init(x_sq);
        mpz_init(m_sq);
        mpz_init(prod);
        mpz_init(diff);

        mpz_set(x_p,P.x);
        mpz_set(y_p,Q.y);
         


        mpz_pow_ui(x_sq,x_p,2);
        mpz_mul_ui(x_sq,x_sq,3);
        mpz_add(x_sq,x_sq,a);
        
        mpz_mod(x_sq,x_sq,p);

        mpz_mul_ui(prod,y_p,2);
        mpz_invert(prod, prod, p);
        mpz_mod(prod,prod,p);
        

        mpz_mul(prod,prod,x_sq);
        mpz_mod(m,prod,p); // gettimg m here
        // gmp_printf("\n -- M is %Zd \n--",m);
        //---------


        mpz_pow_ui(m_sq,m,2);
        mpz_mul_ui(prod,x_p,2);
        // mpz_neg(prod,prod);
            
        mpz_sub(x_r,m_sq,prod);
        
        mpz_mod(x_r,x_r,p);
        // gmp_printf("\n -- x_r is %Zd \n--",x_r);


        mpz_sub(diff,x_p,x_r);     
        
        mpz_mul(prod,m,diff);
        
        mpz_sub(prod,prod,y_p);
        mpz_set(y_r,prod);
        mpz_mod(y_r,y_r,p);
        // gmp_printf("\n -- y_r is %Zd \n--",y_r);


    mpz_set(R.x,x_r);
    mpz_set(R.y,y_r);
     
    return R;
    } // case 4 point doubling


    else if(mpz_cmp(P.x,Q.x)==0)
    {  
        mpz_t y_p;
        mpz_t y_q;
        mpz_init(y_p);
        mpz_init(y_q);
        mpz_set(y_p,P.y);
        mpz_set(y_q,Q.y);
        
        mpz_neg(y_p,y_p);
        mpz_mod(y_p,y_p,p);
        
        // mpz_mod(y_q,y_q,p);


        if ( (mpz_cmp(y_q,y_p) != 0) || ( mpz_cmp_ui(P.y,0)==1 && mpz_cmp_ui(Q.y,0)==1) )
        { flag =1;
        Point R;
        mpz_init(R.x);
        mpz_init(R.y);

        mpz_set_si(R.x,-1);
        mpz_set_si(R.y,-1);
        return R;
            
        }

    }//case 3

    

    if( flag == 0 ) // or put an else condition
    {

        struct Point R;
        mpz_init(R.x);
        mpz_init(R.y);

        mpz_t temp1,temp2,temp3,temp4,temp5,temp6;
        mpz_init(temp1);
        mpz_init(temp2);
        mpz_init(temp3);
        mpz_init(temp4);
        mpz_init(temp5);
        mpz_init(temp6);

        mpz_sub(temp1,P.y,Q.y); // temp1  = yp - yq 

        mpz_mod(temp6,temp1,p);

        // gmp_printf("temp 1 is %Zd , temp 6 is %Zd \n",temp1,temp6);

        mpz_sub(temp2,P.x,Q.x); // temp2  = xp - xq
        mpz_mod(temp2,temp2,p);

        mpz_invert(temp3,temp2,p); //  temp 3 =  mod inv of tmep2
        mpz_mul(temp4,temp1,temp3); // temp 4 =  temp1*temp3
        mpz_mod(temp4,temp4,p); // temp4 mod p

        // gmp_printf("temp 4 is %Zd \n ",temp4);
        
        // m is temp4 

        mpz_t x_r;
        mpz_t y_r;
        mpz_t t;
        mpz_t m_power;
        mpz_t m;
        mpz_t m_sq;

        mpz_init(m);
        mpz_init(x_r);
        mpz_init(y_r);
        mpz_init(t);
        mpz_init(m_power);
        mpz_init(m_sq);

        mpz_set_si(m_power,2);
        mpz_set(m,temp4);
        
        // gmp_printf("m is %Zd \n ",m);

        // mpz_powm(m_sq,m,m_power,p);

        mpz_pow_ui(m_sq,m,2);
        mpz_sub(m_sq,m_sq,P.x);
        mpz_sub(m_sq,m_sq,Q.x);

        mpz_mod(x_r,m_sq,p);
        
        // gmp_printf("xr is %Zd \n ",x_r);

        
        mpz_t sum;
        mpz_init(sum);
        mpz_t diff;
        mpz_init(diff);

        mpz_sub(diff,x_r,P.x);
        mpz_mul(diff,m,diff);

        
        mpz_add(diff,diff,P.y);

        mpz_mod(y_r,diff,p);
        mpz_neg(y_r,y_r);
        mpz_mod(y_r,y_r,p);


        // gmp_printf("yr is %Zd \n ",y_r);

        // gmp_printf("m_sq  is %Zd \n ",m_sq);

        mpz_set(R.x,x_r);
        mpz_set(R.y,y_r);
        // std::printf("bro %s","");
        


    return(R);

    }

}

// Point Doubling(Point P, Point Q, mpz_t p)
// {
//     struct Point R;


//     return R;
// }

Point Multiplication ( Point P, mpz_t p, mpz_t a, mpz_t b, int n)
{
 
    string s = binarystring(n);
    Point result,q;
    mpz_init(result.x);
    mpz_init(result.y);

    mpz_set_si(result.x,-1);
    mpz_set_si(result.y,-1);

    //  mpz_init(q.x);
    //  mpz_init(q.y);

    int i = s.length() - 1;

    if(s.at(i)=='1' && (i == s.length()-1) )
        { 
            mpz_set(result.x,P.x);
            mpz_set(result.y,P.y);
        }

    for(i=s.length()-2;i>=0;i--)
    {
        P = Addition(P,P,p,a,b);
        
        if(s.at(i)=='1')
            {
                result = Addition(result,P,p,a,b);
            }
            
    }

    return result;
}

Point Subtraction( Point P, Point Q, mpz_t p, mpz_t a , mpz_t b)
{
    struct Point R;
    mpz_init(R.x);
    mpz_init(R.y);

    mpz_neg(Q.y,Q.y);
    mpz_mod(Q.y,Q.y,p);

    R = Addition(P,Q,p,a,b);

    return R;

}   



int main()
{   

    int n,choice;
    printf("Enter 1 for interactive mode and 0 for static mode  : %s","");
    scanf("%d",&n);

    mpz_t p;
    mpz_t a;
    mpz_t b;
    //int n;
    if(n==1)
    {
        
            mpz_init(p);
            mpz_init(a);
            mpz_init(b);
            std::printf("Enter p %s","");
            
            gmp_scanf ("%Zd", p);

            std::printf("Enter a %s","");
            
            gmp_scanf ("%Zd", a);

            std::printf("Enter b %s","");
            
            gmp_scanf ("%Zd", b);

            while(1)
            {
            printf("\n%s","");
            std::printf("Enter 1 for multiplication ; 2 for Addition ; 3 for subtraction ; 4 for negation ;  5 for calculating ehter x lies on curve ; 8 to exit%s : ","");

            gmp_scanf ("%d",&choice);

            struct Point P;
            struct Point Q;

            mpz_init_set_si(P.x,17);
            mpz_init_set_si(P.y,10);
            mpz_init_set_si(Q.x,12); // 11
            mpz_init_set_si(Q.y,3); // 10

            Point temp;
            
            if(choice == 8)
                break;

            if(choice==1)
            {
                temp = Multiplication(P,p,a,b,2);
                gmp_printf("after multiplication, R.x : %Zd , R.y : %Zd",temp.x,temp.y);
            }

            if(choice == 2)
            {
                temp = Addition(P,Q,p,a,b);
                gmp_printf(" after Addition, R.x : %Zd , R.y : %Zd ",temp.x,temp.y);
            }   

                  if(choice == 3)
            {
                temp = Subtraction(P,Q,p,a,b);
                gmp_printf(" after Addition, R.x : %Zd , R.y : %Zd",temp.x,temp.y);
            }   


                if(choice == 4)
                {
                    temp = Negate(P,p,a,b);
                    gmp_printf(" after Addition, R.x : %Zd , R.y : %Zd ",temp.x,temp.y);
                
                }   

                if(choice == 5)
                {
                        mpz_t x;
                        mpz_init(x);
                        printf("enter x : %s"," ");
                        gmp_scanf("%Zd",x);
                        // #mpz_set_ui(x,1); // set the x value for plugging into variable
                        calculate(x,p);
                
                }   

         }


        }

    
    

    if (n == 0)
    {
        // mpz_init_set_si(p,7);
        // mpz_init_set_si(a,-5);
        // mpz_init_set_si(b,8);


        FILE *filep;
        filep = fopen("ecc_parameters.txt","r");
        if (filep == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        mpz_t p,a,b;
        mpz_init(p);
        mpz_init(a);
        mpz_init(b);
        gmp_fscanf(filep,"%Zd Zd Zd\n",p,a,b);
        
        fclose(filep);


        // mpz_tdiv_r(p,p,a);
        // gmp_printf(" %Zd \n\n",p);
        
        struct Point P;
        struct Point Q;
        // Point Addition;

        Point temp;

        // temp = Multiplication(P,p,a,b,5);
        // gmp_printf("R.x %Zd , R.y %Zd",temp.x,temp.y);

        ///////////////////////////////////////////////////

        //TODO:  Case 1a: Uncomment the following block to try out ADDITION on two different points P and Q  
       
        //NOTE: You can set custom x and y values accordingly below 
        // mpz_init_set_si(P.x,30);
        // mpz_init_set_si(P.y,15);
        // mpz_init_set_si(Q.x,35); // 
        // mpz_init_set_si(Q.y,8); //

        // temp = Addition(P,Q,p,a,b);
        // gmp_printf("After addition  Rx : %Zd | Ry : %Zd ",temp.x,temp.y);
              
        ///////////////////////////////////////////////////
        

        //TODO:  Case 1b: Uncomment the following block to try out ADDITION on two same points P and P
        //NOTE: You can set custom x and y values accordingly below 
        // mpz_init_set_si(P.x,35);
        // mpz_init_set_si(P.y,8);
        // mpz_init_set_si(Q.x,35); 
        // mpz_init_set_si(Q.y,8); 

        // temp = Addition(P,Q,p,a,b);
        // gmp_printf("After addition :  R.x : %Zd ; R.y : %Zd ",temp.x,temp.y);
              
        ///////////////////////////////////////////////////
        
        //TODO:  Case 1c: Uncomment the following block to try out ADDITION on points P and infinity 
        //NOTE: You can set custom x and y values accordingly below 
        // mpz_init_set_si(P.x,35);
        // mpz_init_set_si(P.y,8);
        // mpz_init_set_si(Q.x,-1); // 11
        // mpz_init_set_si(Q.y,-1); // 10

        // temp = Addition(P,Q,p,a,b);
        // gmp_printf("After addition :  R.x : %Zd ; R.y : %Zd ",temp.x,temp.y);
              
        ///////////////////////////////////////////////////
        
        //TODO:  Case 2: Uncomment the following block to try out SUBTRACTION on two different points P and Q  
        
        // mpz_init_set_si(P.x,37);
        // mpz_init_set_si(P.y,6);
        // mpz_init_set_si(Q.x,31); // 11
        // mpz_init_set_si(Q.y,6); // 10

        // temp = Subtraction(P,Q,p,a,b);
        // gmp_printf("After Subtraction :  R.x : %Zd ; R.y : %Zd ",temp.x,temp.y);
              
        ///////////////////////////////////////////////////

        //TODO:  Case 3: Uncomment the following block to try out MULTIPLICATION on point P  
        
        // mpz_init_set_si(P.x,37);
        // mpz_init_set_si(P.y,6);
        // mpz_init_set_si(Q.x,12); // 11
        // mpz_init_set_si(Q.y,3); // 10

        // temp = Multiplication(P,p,a,b,n);
        // gmp_printf("After Multiplication :  R.x : %Zd ; R.y : %Zd ",temp.x,temp.y);
        
        //////////////////////////////////////////////////


        //TODO:  Case 4: Uncomment the following block to try out NEGATION on a point P
        
        // mpz_init_set_si(P.x,37);
        // mpz_init_set_si(P.y,6);
        // mpz_init_set_si(Q.x,31); // 11
        // mpz_init_set_si(Q.y,6); // 10

        // temp = Negate(P,p,a,b);
        // gmp_printf("After Negation :  R.x : %Zd ; R.y : %Zd ",temp.x,temp.y);
        
        // //////////////////////////////////////////////////


        //TODO:  Case 5: Uncomment the following block to try out VERIFICATION whether a point P lies on CURVE         
        
        // mpz_init_set_si(P.x,37);
        // mpz_init_set_si(P.y,6);
        // mpz_init_set_si(Q.x,12); // 11
        // mpz_init_set_si(Q.y,3); // 10


        // mpz_t x;
        // mpz_init(x);
        // mpz_set_ui(x,1); // set the x value for plugging into variable
        // calculate(x,p);

        //////////////////////////////////////////////////





      
    }


    return 0;
}







