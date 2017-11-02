// slist1.c ... show all student records via read()

#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   int stufd = open("Students1",O_RDONLY);
   if (stufd < 0)
      error(errno, errno, "Can't open student data");

   Student stude;
   while (read(stufd, &stude, sizeof(Student)) > 0)
      showStudentData(stude);

   close(stufd);
   return 0;
}


// --------------------------------------------------- //

// sadd1.c ... add a student record via write()

#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include "Student.h"

// Student = (id,given,family,prog,wam)

int main(void)
{
   int stufd = open("Students1",O_WRONLY|O_APPEND);
   if (stufd < 0)
      error(errno, errno, "Can't open student data");

   Student stude;
   if (getStudentData(&stude) < 0)
      error(1, 0, "Invalid student data");
   showStudentData(stude);

   ssize_t nbytes;
   nbytes = write(stufd, &stude, sizeof(Student));
   if (nbytes < 0)
      error(errno, errno, "Write failed");
   if (nbytes != sizeof(Student))
      error(errno, errno, "Only wrote %d", nbytes);
   close(stufd);

   return 0;
}
