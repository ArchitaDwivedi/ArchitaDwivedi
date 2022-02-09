#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"
#include "Enrollment.h"

// create global dictionaries
 dictionary	CourseDict;
 dictionary	StudentDict;



// -------------------------------------------
// adds *e to the CourseDict.
// Checks if *e already exists, if so print error message
// and don't update the dictionary.  Else update dictionary.
// -------------------------------------------
// Description:- This function takes in a course_element.
// We use this function to a course to the Course Dictionary.
// First we check if a node with that course_element's key
// already exists. If it does, we dont need to append it.
// Otherwise, we simply use insert() and append the node 
// in the element Course dictionary.
// -------------------------------------------
void addCourse( course_element *e )
{


    if( find( &CourseDict, e->key) != NULL ){
      printf("Error adding Course: Course already exists!\n");
      return;
    }

    else
    {
      insert(&CourseDict, (element *)e );
    }
  return;
}

// -------------------------------------------
// deletes course whose ID/key is c_key from the CourseDict.
// This should check if the course to be deleted exists.
// If not, just print an error message: "Course does not exist."
// If the course exists, then this will also drop students who
// are currently enrolled in the course and then remove course
// from course dict
// -------------------------------------------
// Description:- This function takes in a course
// key.
// We first start by checking if the course we want to
// delete is in the Course Dictionary. If it doesnt we
// return. Otherwise, we get that node's value field,
// which should be of course_value type. Next, we get
// the list of students from that course_value field
// We loop through the nodes and iterate over the students
// and call drop on them, to drop the course from the students'
// list and drop the student from the course's list as well.
// Finally once all students are deleted, we call delete()
// to delete the main Course Dictionary node.
// -------------------------------------------
void delCourse( char *c_key )
{
   node_t *temp =  find(&CourseDict, c_key);
    if (temp == NULL){ // use find as above
      printf("Course does not exist.\n");
      return;
    }


    else{
     course_value *c = temp->value;
      node_t *cc = c->list;
      for( int i = 0 ; i < c -> num_students ; i++ ){ 
        drop(cc->key, c_key);
        cc = cc->next;
      }
//      free(temp);
      delete(&CourseDict,c_key);

    }

  return;
}



// -------------------------------------------
// enrolls student into course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is already enrolled in the course.  Also check if course
// is full or if student has reached max number of courses.
// If there's any error, print a message and don't enroll
// the student.  If there's no errors, update both dictionaries.
// -------------------------------------------
// Description:- This function takes in a student key and
// course key.
// We first get the main Course Dictinary and Student
// Dictionary node. If the course node doesnt exist, we
// exit. If the student node doesnt exist, we first 
// create a student element. Then we copy the student key
// into it. For the value field, we first use newNode to
// malloc space of a student_value type, to assign to the 
// student element's value field. Then we set its members.
// Finally, we insert this node to the Student Dictionary.
// Next, we get the student node's value field and 
// course node's value field. Then we use findList() to 
// check if the student is already enrolled in the course.
// Similarly, we do basic capacity checks. if something
// violates the condition we exit. Else, we
// malloc space for nodes. Copy course key and student 
// key into the nodes. Finally we append the course node
// to the student dictionary's list of courses and the 
// student node to the course dictionary's list of students.
// We update the counters and return.
// -------------------------------------------
void enroll( char *s_key, char *c_key )
{
  int c = 0;
  node_t *course_node;
  node_t *student_node;


	// decalare vars for course info and student info corresponding to
	// the value fields of each node/element
  course_value *c_node_val;
  student_value *s_node_val = NULL;



	// fetch course and student corresponding to keys from respective dicts
	// initialize vars depending on whether student/course with given key
	// is in the dictionary
  course_node = find(&CourseDict, c_key);
  student_node = find(&StudentDict, s_key);



  // if course doens't exist, print error and return
  if (!course_node){
    printf("Course Does not Exist!\n");
    return;
  }
	
	

	// if student does not exist, insert student to student dict
	if (!student_node){

    // malloc space
    student_element *se =  (student_element *)malloc(sizeof(student_element *)); 
    
    // student id
    memcpy(se->key, s_key, 5); 


    se->value = (student_value *) newNode('s');
    se->value->num_courses = 0;
    se->value->list = NULL;
    

    insert(&StudentDict, (element *)se);


    s_node_val = se->value;
    c = 1;
  }	



  // if s_node_val is not set it
  if ( c != 1){
    s_node_val = student_node->value;
  }
  c_node_val = course_node->value;
  

  // finding student key in CourseDict's list of students!
  node_t *is_enrolled = findList(c_node_val->list, s_key);


  // if student is found, means student is enrolled!
  if (is_enrolled != NULL){
    printf("Error! Student already enrolled in course!\n");
    return;
  }

  // capacity check
  if (c_node_val->num_students >= c_node_val->capacity){
    printf("Error! Course capacity reached!\n");
    return;
  }


  // if student is already in 2 courses  
  if (s_node_val->num_courses >= 2){
    printf("Cannot enroll in more than 2 courses.\n");
    return;  
  }



  // create space
  node_t *to_enroll = (node_t *)malloc(sizeof(node_t));
  node_t *acc = (node_t *)malloc(sizeof(node_t));
  
  memcpy(to_enroll->key, s_key,5);

  // insert node to course dictionary's list of students
  insertList(&c_node_val->list, to_enroll); 
  // update counter
  c_node_val->num_students++;




  memcpy(acc->key, c_key,5);

  // insert node to student dictionary's list of courses
  insertList(&s_node_val->list, acc); 
  // update counter
  s_node_val->num_courses++;


  return;
}





// -------------------------------------------
// drops a student from course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is enrolled in the course.  If any error is encountered,
// print an error message.
// If there are no errors, update both dictionaries.
// -------------------------------------------
// Description:- This function takes in a student key
// and a course key.
// We first get the main Course Dictinary and Student
// Dictionary node. If the nodes dont exist we return.
// Then we get the value field of those nodes. Those nodes
// are of student_value and course_value type. Finally,
// we get the list of those value fields. Then we check
// if a there a student in the course dictionary and
// if there is a course in the student dictionary.
// If these dont exist, we exit. Otherwise, we call
// deleteList() to delete those nodes and return.
// -------------------------------------------
void drop( char *s_key, char *c_key )
{
	// fetch nodes corresponding to student and course from
	// respective dicts having the given keys
  node_t *course_node = find(&CourseDict, c_key);
  node_t *student_node = find(&StudentDict, s_key);



	// if found no such course, print message and return
  if (!course_node || !student_node){
    printf("No node is found!\n");
    return;
  }


  student_value *s_node_val = student_node->value;
  course_value *c_node_val = course_node->value;

  node_t *cl = c_node_val->list; 
  node_t *sl = s_node_val->list; 
  
  
  node_t *is_en = NULL;
  is_en = findList(cl, s_key);
  node_t *is_st = NULL;
  is_st = findList(sl, c_key);

  
  if (!is_en){
    printf("Student not enrolled in class!\n");
    return;
  }

  if (!is_st){
    printf("Class not in student's list!\n");
    return;
  }


  if (c_node_val->num_students > 0 ){
    deleteList(&cl, is_en);
    c_node_val->num_students--;
  }



  if (s_node_val->num_courses > 0  ){
    deleteList(&sl, is_st);
    s_node_val->num_courses--;
  }


  return;
}

// -------------------------------------------
// prints the StudentDict.
// -------------------------------------------
void printStudents()
{
	printf("Students:\n");
	print( &StudentDict );
  return;
}

// -------------------------------------------
// prints the CourseDict.
// -------------------------------------------
void printCourses()
{
	printf("Courses:\n");
	print( &CourseDict );
  return;
}


// -------------------------------------------
// Don't edit the code below.  This is the driver code to test
// your implementation.
// -------------------------------------------
int main()
{
	char	line[100];
	char 	*command;
	int	done = 0;

        course_element  *ce;
        student_element *se;

	char	*course_key;
	char	*student_key;

	// initialize dictionaries
	create( &CourseDict, 20 );
	create( &StudentDict, 20 );

	// process input
	while( ! done )
	{
		// read an entire line as a string
		fgets(line, 100, stdin);

		// pulls command code, assume comma or tab separated
		command = strtok( line, " \t" );

		if (strncmp(command, "ex",2) == 0)
			{	printf( "Exited Program\n" );
				done = 1;
			}
		else if (strncmp(command, "ac",2)==0)		// add a new course
			{
				// printf("ac\n");
				
				// Parse and package rest of line into a course_element
				ce = (course_element *) malloc( sizeof(course_element) );
				course_key = strtok( NULL, " " );
				printf( "Adding course: %s\n", course_key );
				memcpy( (*ce).key, course_key, 5 );
				ce->value = (void *) newNode( 'c' );
				ce->value->capacity = atoi( strtok( NULL, " " ) );
				ce->value->num_students = 0;
				ce->value->list = NULL;
				addCourse( ce );
			}
		else if (strncmp(command, "dc",2)==0)		// delete a course
			{
				course_key = strtok( NULL, " " );
				delCourse(course_key);
				printf("Delete Course Complete\n");
			}
		else if (strncmp(command, "en",2)==0)		// enroll a student
			{
				// printf("en\n");
				
				// Parse and package rest of line into a course_element
				student_key = strtok( NULL, " " );
				course_key = strtok( NULL, " " );
				printf( "Enrolling student: %s into course: %s\n", student_key, course_key );
				enroll( student_key, course_key );
			}
		else if (strncmp(command, "dr",2)==0)		// drop a student
			{
				student_key = strtok( NULL, " " );
				course_key = strtok( NULL, " " );
				printf( "Dropping student: %s from course: %s\n", student_key, course_key );
				drop(student_key, course_key);
			}
		else if (strncmp(command, "ps",2)==0)		// print students
			printStudents();
		else if (strncmp(command, "pc",2)==0)		// print courses
			printCourses();
		else printf("Unrecognized command: %2s\n", command);


	}

	return 0;
}

