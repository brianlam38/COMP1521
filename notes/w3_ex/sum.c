// sum elements in an array

int sum(int a[], int n)
{
   int sum = 0;
   for (int i = 0; i < n; i++)
      sum += a[i];
   return sum;
}

int sum(int a[], int n)
{
   int sum = 0;
   int *p;
   int *last = &a[n-1];

   p = a; // p = &a[0];
   while (p <= last) {
      sum += *p;
      p++;
   }
}
