#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Student
{
public:
    string SID;
    string St_Name;
    string Father_Name;
    string Gender;
    string Address;
    string city_name;
    string DOB;
    string Reg_Date;
    string Reg_Status;
    string Degree_Status;
    string Last_Degree;
};

class Course
{
public:
    string SID;
    string Degree;
    string Semester;
    string Course_Code;
    string Marks;
    string discipline;
};

string ConvertDate(string date)
{
    vector<string> dateParts;
    string part;
    for (char c : date)
    {
        if (c == '-')
        {
            dateParts.push_back(part); // feeds part before - say 01-02-94 i.e 01 and then 02
            part = "";
        }
        else
        {
            part += c;
        }
    }
    dateParts.push_back(part); // 94 part
    string monthAbbreviation;
    if (dateParts[1] == "01" || dateParts[1] == "1")
    {
        monthAbbreviation = "Jan";
    }
    else if (dateParts[1] == "02" || dateParts[1] == "2")
    {
        monthAbbreviation = "Feb";
    }
    else if (dateParts[1] == "03" || dateParts[1] == "3")
    {
        monthAbbreviation = "Mar";
    }
    else if (dateParts[1] == "04" || dateParts[1] == "4")
    {
        monthAbbreviation = "Apr";
    }
    else if (dateParts[1] == "05" || dateParts[1] == "5")
    {
        monthAbbreviation = "May";
    }
    else if (dateParts[1] == "06" || dateParts[1] == "6")
    {
        monthAbbreviation = "Jun";
    }
    else if (dateParts[1] == "07" || dateParts[1] == "7")
    {
        monthAbbreviation = "Jul";
    }
    else if (dateParts[1] == "08" || dateParts[1] == "8")
    {
        monthAbbreviation = "Aug";
    }
    else if (dateParts[1] == "09" || dateParts[1] == "9")
    {
        monthAbbreviation = "Sep";
    }
    else if (dateParts[1] == "10")
    {
        monthAbbreviation = "Oct";
    }
    else if (dateParts[1] == "11")
    {
        monthAbbreviation = "Nov";
    }
    else if (dateParts[1] == "12")
    {
        monthAbbreviation = "Dec";
    }
    return dateParts[0] + "-" + monthAbbreviation + "-" + dateParts[2];
}

bool IsNameInFile(string name, string fileName)
{
    ifstream openfile(fileName);
    string line;
    while (getline(openfile, line))
    {
        if (line == name)
        {
            return true;
        }
    }
    return false;
}

bool isNameAlreadyExists(const string filename, const string name)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line == name)
        {
            return true;
        }
    }

    return false;
}

void writeToGenderFile(const Student student)
{
    ofstream outfile2;
    string f;
    if (student.Gender == "M")
    {
        f = "malenames.txt";
        outfile2.open("malenames.txt", ios_base::app);
    }
    else if (student.Gender == "F")
    {
        f = "femalenames.txt";
        outfile2.open("femalenames.txt", ios_base::app);
    }

    string firstname;

    for (char x : student.St_Name)
    {
        if (x == ' ' || x == '.')
        {
            break; // Stop extracting after encountering a space or period
        }
        else
        {
            firstname += x;
        }
    }

    if (firstname.length() < 3)
    {
        string secondname;
        bool foundSpace = false;

        for (char x : student.St_Name)
        {
            if (x == ' ')
            {
                foundSpace = true;
            }
            else if (foundSpace)
            {
                secondname += x;
            }
        }

        if (!secondname.empty())
        {
            firstname = secondname;
        }
    }

    if (!isNameAlreadyExists(f, firstname))
    {
        outfile2 << firstname << endl;
    }

    outfile2.close();
}

string standardizeCityName(const string &city)
{
    string standardizedCity = city;
    transform(standardizedCity.begin(), standardizedCity.end(), standardizedCity.begin(), ::tolower);

    // Handle specific city mappings
    unordered_map<string, string> cityMappings = {
        {"dg khan", "Dera Ghazi Khan"},
        {"di khan", "Dera Ismail Khan"},
        {"lhr", "Lahore"},
        {"shekhopura", "Sheikhupura"},
        {"isb", "Islamabad"},
        {"khan", "Dera Ghazi Khan"},
        {"rwp", "Rawalpindi"},
        {"dgk", "Dera Ghazi Khan"},
        {"mul", "Multan"},
        {"mux", "Multan"},
        {"fsb", "Faislabad"},
        {"kar", "Karachi"},
        {"sheikhapura", "Sheikhupura"},
        {"psh", "Peshawar"},
        {"bhv", "Bahawalpur"},
        {"lhe", "Lahore"},
        {"noshera", "Nowshera"},
        {"fsd", "Faislabad"},
        {"khi", "Karachi"}
      
    };

    // Check if the city has a specific mapping
    auto it = cityMappings.find(standardizedCity);
    if (it != cityMappings.end())
    {
        return it->second;
    }

    // Capitalize the first letter of each word
    bool capitalizeNext = true;
    for (size_t i = 0; i < standardizedCity.length(); ++i)
    {
        if (capitalizeNext && isalpha(standardizedCity[i]))
        {
            standardizedCity[i] = toupper(standardizedCity[i]);
            capitalizeNext = false;
        }
        else if (standardizedCity[i] == ' ')
        {
            capitalizeNext = true;
        }
    }

    return standardizedCity;
}



int countStudentsWithMoreThanFiveCourses(const vector<Course>& ACdata) {
    set<string> uniqueStudents;
    int moreThanFive = 0;
    int coursesCounter = 0;
    string currentSID = "";

    for (int i = 0; i < ACdata.size(); i++) {
        if (ACdata[i].SID == currentSID) {
            coursesCounter++;
        } else {
            currentSID = ACdata[i].SID;
            coursesCounter = 1;
        }

        if (coursesCounter > 5 && uniqueStudents.find(currentSID) == uniqueStudents.end()) {
            moreThanFive++;
            uniqueStudents.insert(currentSID);
        }
    }

    return moreThanFive;
}

int main()
{

    // Lahore Student Data
    string Studentfile_names[] = {
        "Lhr_Student_94.txt", "Lhr_Student_95.txt", "Lhr_Student_96.txt", "Lhr_Student_97.txt", "Lhr_Student_98.txt",
        "Lhr_Student_99.txt", "Lhr_Student_100.txt", "Lhr_Student_101.txt", "Lhr_Student_102.txt", "Lhr_Student_103.txt",
        "Lhr_Student_104.txt", "Lhr_Student_MS_101.txt", "Lhr_Student_MS_102.txt", "Lhr_Student_MS_103.txt", "Lhr_Student_MS_104.txt",
        "Transfer.txt"};

    ifstream in;
    vector<Student> Sdata;
    string line; // to store one line
    for (int i = 0; i < 16; i++)
    {
        in.open(Studentfile_names[i]); // HAS DATA OF 94 ONLY
        getline(in, line);             // discard first line
        while (getline(in, line))
        {                          // takes input of one line
            string field;          // stores part of the one line
            vector<string> fields; // to store all parts of a line
            for (char b : line)
            { // comes out when line ends
                if (b == ',')
                {
                    fields.push_back(field); // when comma. store field in vector,, full line stored
                    field = "";              // field emptied again
                }
                else
                {
                    field += b; // storing all characters in field until we get a comma
                }
            }
            fields.push_back(field);

            // gender 0 and 1 ---> M and F
            string gender;
            if (fields[3] == "0")
            {
                gender = "M";
            }
            else if (fields[3] == "1")
            {
                gender = "F";
            }
            else
            {
                gender = fields[3];
            }

            string address;
            string city;

            address = fields[4];
            size_t pos = address.rfind(" ");
            if (pos != string::npos)
            {
                city = address.substr(pos + 1);
                city = standardizeCityName(city);
            }

            Student student;

            student.SID = fields[0];
            student.St_Name = fields[1];
            student.Father_Name = fields[2];
            student.Gender = gender;
            student.Address = address;
            student.city_name = city;
            student.DOB = fields[5];
            student.Reg_Date = fields[6];
            student.Reg_Status = fields[7];
            student.Degree_Status = fields[8];
            student.Last_Degree = fields[9];

            Sdata.push_back(student); // all data added into vector Sdata[i].SID Sdata[i].DOB etc

            writeToGenderFile(student); // function to extract names into male + female files
        }
        in.close();
    }
    
    
    
    // Lahore course/detail data
    string Detailfile_names[] = {
        "Lhr_Detail_94.txt", "Lhr_Detail_95.txt", "Lhr_Detail_96.txt", "Lhr_Detail_97.txt", "Lhr_Detail_98.txt",
        "Lhr_Detail_99.txt", "Lhr_Detail_100.txt", "Lhr_Detail_101.txt", "Lhr_Detail_102.txt", "Lhr_Detail_103.txt",
        "Lhr_Detail_104.txt", "Lhr_Detail_MS_101.txt", "Lhr_Detail_MS_102.txt", "Lhr_Detail_MS_103.txt",
        "Lhr_Detail_MS_104.txt"

    };

    ifstream in2;
    vector<Course> Cdata;
    string line2; // to store one line
    for (int i = 0; i < 15; i++)
    {
        in2.open(Detailfile_names[i]);
        getline(in2, line2); // discard first line
        while (getline(in2, line2))
        {
            string field;
            vector<string> fields;
            for (char b : line2)
            {
                if (b == ',')
                {
                    fields.push_back(field);
                    field = "";
                }
                else
                {
                    field += b;
                }
            }
            fields.push_back(field);

            Course course;
            string discipline;

            if (i < 11)
            {

                discipline = fields[5];
            }
            else if (i >= 11)
            {
                discipline = fields[5].substr(3);
            }

            course.SID = fields[0];
            course.Degree = fields[1];
            course.Semester = fields[2];
            course.Course_Code = fields[3];
            course.Marks = fields[4];
            course.discipline = discipline;

            Cdata.push_back(course);
        }
        in2.close();
    }





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Peshawar Course data
    ifstream in3;
    vector<Course> PCdata;
    string line3;

    string PDetailfile_names[] = {
        "BS_P_94_Reg.txt", "BS_P_95_Reg.txt", "BS_P_96_Reg.txt", "BS_P_97_Reg.txt", "BS_P_98_Reg.txt",
        "BS_P_99_Reg.txt", "BS_P_100_Reg.txt", "BS_P_101_Reg.txt", "BS_P_102_Reg.txt", "BS_P_103_Reg.txt",
        "BS_P_104_Reg.txt", "MS_P_101_Reg.txt", "MS_P_102_Reg.txt", "MS_P_103_Reg.txt",
        "MS_P_104_Reg.txt"

    };
    for (int i = 0; i < 15; i++)
    {
        in3.open(PDetailfile_names[i]);
        getline(in3, line3); // discard first line
        while (getline(in3, line3))
        {
            string field;
            vector<string> fields;
            for (char b : line3)
            {
                if (b == ',')
                {
                    fields.push_back(field);
                    field = "";
                }
                else
                {
                    field += b;
                }
            }
            fields.push_back(field);

            Course course;
            course.SID = fields[0];
            string degree;
            string discipline;
            if (i < 11)
            {
                degree = "BS";
                discipline = fields[3];
            }
            else if (i >= 11)
            {
                degree = "MS";
                discipline = fields[3].substr(3);
            }
            course.Degree = degree;
            string semesterYear = fields[5]; // formatting according to Lahore
            if (semesterYear.size() == 4)
            {
                semesterYear = semesterYear.substr(2);
            }
            course.Semester = fields[4] + semesterYear;

            course.Course_Code = fields[1];
            course.Marks = fields[2];
            course.discipline = discipline;

            PCdata.push_back(course);
        }
        in3.close();
    }

    // Peshawar Student data

    string PStudentfile_names[] = {
        "BS_P_94_Student.txt",
        "BS_P_95_Student.txt",
        "BS_P_96_Student.txt",
        "BS_P_97_Student.txt",
        "BS_P_98_Student.txt",
        "BS_P_99_Student.txt",
        "BS_P_100_Student.txt",
        "BS_P_101_Student.txt",
        "BS_P_102_Student.txt",
        "BS_P_103_Student.txt",
        "BS_P_104_Student.txt",
        "MS_P_101_Student.txt",
        "MS_P_102_Student.txt",
        "MS_P_103_Student.txt",
        "MS_P_104_Student.txt",
    };

    ifstream in4;
    string line4;
    vector<Student> PSdata;
    for (int i = 0; i < 15; i++)
    {
        in4.open(PStudentfile_names[i]);
        getline(in4, line4); // discard first line
        while (getline(in4, line4))
        {
            string field;
            vector<string> fields;
            for (char b : line4)
            {
                if (b == ',')
                {
                    fields.push_back(field);
                    field = "";
                }
                else
                {
                    field += b;
                }
            }
            fields.push_back(field);

            Student student;
            student.SID = fields[0];
            student.St_Name = fields[1];
            student.Father_Name = fields[2];

            string name;
            string nametobeadded;
            vector<string> firstname;
            for (char a : student.St_Name)
            {
                if (a == ' ')
                {
                    firstname.push_back(name);
                    name = "";
                }
                else
                {
                    name += a;
                }
            }

            if (firstname.size() > 1 && firstname[0].length() < 3)
            {
                nametobeadded = firstname[1];
            }
            else if (!firstname.empty() && (firstname[0].length() > 3 || firstname[0].length() == 3))
            {
                nametobeadded = firstname[0];
            }
            else
            {
                nametobeadded = "";
            }

            string malenames = "malenames.txt";
            string femalenames = "femalenames.txt";
            if (IsNameInFile(nametobeadded, malenames))
            {
                student.Gender = "M";
            }
            else if (IsNameInFile(nametobeadded, femalenames))
            {
                student.Gender = "F";
            }
            else if (IsNameInFile(nametobeadded, malenames) && IsNameInFile(nametobeadded, femalenames))
            {
                student.Gender = "M";
            }
            else
            {
                student.Gender = "";
            }

            string address;
            string city;

            address = fields[3];
            size_t pos = address.rfind(" ");
            if (pos != string::npos)
            {
                city = address.substr(pos + 1);
                city = standardizeCityName(city);
            }

            // student.Gender = fields[3];

            string newDOB = ConvertDate(fields[4]);
            string newRegDate = ConvertDate(fields[6]);

            student.Address = address;
            student.city_name = city;
            student.DOB = newDOB;
            student.Reg_Date = newRegDate;
            student.Reg_Status = fields[7];
            student.Degree_Status = fields[8];
            student.Last_Degree = fields[5];

            PSdata.push_back(student);
        }
        in4.close();
    }

    // PSdata[0].Gender = "Gender";

    // gathering datas together

    // student data:
    ofstream sout;
    sout.open("AllStudents.txt");

    // Write the headings
    sout << "SID,St_Name,Father_Name,Gender,Address,City,DOB,Reg_Date,Reg_Status,Degree_Status,Last_Degree" << endl;

    // Write Lahore student data
    for (int i = 0; i < Sdata.size(); i++)
    {
        sout << Sdata[i].SID << ",";
        sout << Sdata[i].St_Name << ",";
        sout << Sdata[i].Father_Name << ",";
        sout << Sdata[i].Gender << ",";
        sout << Sdata[i].Address << ",";
        sout << Sdata[i].city_name << ",";
        sout << Sdata[i].DOB << ",";
        sout << Sdata[i].Reg_Date << ",";
        sout << Sdata[i].Reg_Status << ",";
        sout << Sdata[i].Degree_Status << ",";
        sout << Sdata[i].Last_Degree << endl;
    }

    // Write Peshawar student data
    for (int i = 0; i < PSdata.size(); i++)
    {
        sout << PSdata[i].SID << ",";
        sout << PSdata[i].St_Name << ",";
        sout << PSdata[i].Father_Name << ",";
        sout << PSdata[i].Gender << ",";
        sout << PSdata[i].Address << ",";
        sout << PSdata[i].city_name << ",";
        sout << PSdata[i].DOB << ",";
        sout << PSdata[i].Reg_Date << ",";
        sout << PSdata[i].Reg_Status << ",";
        sout << PSdata[i].Degree_Status << ",";
        sout << PSdata[i].Last_Degree << endl;
    }

    sout.close();

    // student details:

    ofstream sout2;
    sout2.open("AllDetails.txt");

    // Write the headings
    sout2 << "SID,Degree,Semester,Course_Code,Marks,Discipline" << endl;

    // Write Lahore course data
    for (int i = 0; i < Cdata.size(); i++)
    {
        sout2 << Cdata[i].SID << ",";
        sout2 << Cdata[i].Degree << ",";
        sout2 << Cdata[i].Semester << ",";
        sout2 << Cdata[i].Course_Code << ",";
        sout2 << Cdata[i].Marks << ",";
        sout2 << Cdata[i].discipline << endl;
    }

    // Write Peshawar course data
    for (int i = 0; i < PCdata.size(); i++)
    {
        sout2 << PCdata[i].SID << ",";
        sout2 << PCdata[i].Degree << ",";
        sout2 << PCdata[i].Semester << ",";
        sout2 << PCdata[i].Course_Code << ",";
        sout2 << PCdata[i].Marks << ",";
        sout2 << PCdata[i].discipline << endl;
    }

    sout2.close();

    // read all students details file.
    ifstream in12;
    vector<Student> ASdata;
    string line12;
    in12.open("AllStudents.txt");
    getline(in12, line12);
    while (getline(in12, line12))
    {                          // takes input of one line
        string field;          // stores part of the one line
        vector<string> fields; // to store all parts of a line
        for (char b : line12)
        { // comes out when line ends
            if (b == ',')
            {
                fields.push_back(field); // when comma. store field in vector,, full line stored
                field = "";              // field emptied again
            }
            else
            {
                field += b; // storing all characters in field until we get a comma
            }
        }
        fields.push_back(field);

        Student student;
        student.SID = fields[0];
        student.St_Name = fields[1];
        student.Father_Name = fields[2];
        student.Gender = fields[3];
        student.Address = fields[4];
        student.city_name = fields[5];
        student.DOB = fields[6];
        student.Reg_Date = fields[7];
        student.Reg_Status = fields[8];
        student.Degree_Status = fields[9];
        student.Last_Degree = fields[10];

        ASdata.push_back(student); // all data added into vector Sdata[i].SID Sdata[i].DOB etc
    }
    in12.close();


    //read all courses file.
    ifstream in21;
    vector<Course> ACdata;
    string line21;
    in21.open("AllDetails.txt");
    getline(in21, line21);
    while (getline(in21, line21))
    {
        string field;
        vector<string> fields;
        for (char b : line21)
        {
            if (b == ',')
            {
                fields.push_back(field);
                field = "";
            }
            else
            {
                field += b;
            }
        }
        fields.push_back(field);

        Course course;
        course.SID = fields[0];
        course.Degree = fields[1];
        course.Semester = fields[2];
        course.Course_Code = fields[3];
        course.Marks = fields[4];
        course.discipline = fields[5];

        ACdata.push_back(course);
    }
    in21.close();

    

    int i0;
    cout<<"1. Statistics for Lahore"<<endl;
    cout<<"2. Statistics for Peshawar"<<endl;
    cout<<"3. Statistics for Lahore and Peshawar combined"<<endl;
    cout<<"Enter 1 or 2 or 3"<<endl<<endl;
    cin>>i0;
    switch(i0)
    {
        case 1:
        {
            set <string> uSID;
            set <string> uDegree;
            set <string> uSemester;
            set <string> uCourse_Code;
            set <string> uMarks;
            set <string> udiscipline;
            int idnull = 0, degreenull = 0, codenull = 0, marksnull = 0, disciplinenull = 0, semnull = 0;

            for (int i=0; i<Cdata.size(); i++){              // adds unique values into the set
                uSID.insert(Cdata[i].SID);                   // unique IDs added to uSID 
                uDegree.insert(Cdata[i].Degree);
                uCourse_Code.insert(Cdata[i].Course_Code);
                uMarks.insert(Cdata[i].Marks);
                udiscipline.insert(Cdata[i].discipline);
                uSemester.insert(Cdata[i].Semester);

                if (Cdata[i].SID.empty()){                 // checks for empty values
                    idnull++;
                }
                if (Cdata[i].Degree.empty()){
                    degreenull++;
                }
                if (Cdata[i].Semester.empty()){
                    semnull++;
                }
                if (Cdata[i].Course_Code.empty()){
                    codenull++;
                }
                if (Cdata[i].Marks.empty()){
                    marksnull++;
                }
                if (Cdata[i].discipline.empty()){
                    disciplinenull++;
                }
            }

            int mfratio =0, male=0, female=0;
            for (int i=0; i<Sdata.size(); i++){
                if (Sdata[i].Gender == "M"){
                    male++;
                }
                else if (Sdata[i].Gender == "F"){
                    female++;
                }
            }

            int morethanfive = 0;
            int coursescounter;
            string current = "";
            for (int i = 0; i < Cdata.size(); i++) {
                if (Cdata[i].SID == current) {
                    coursescounter++;
                } else {
                    current = Cdata[i].SID;
                    coursescounter = 1;
                }
                if (coursescounter > 5) {
                    morethanfive++;
                }
            }



            cout << "Number of unique values for each column in Course data:" << endl;
            cout << "Student ID: " << uSID.size() << endl;
            cout << "Degree: " << uDegree.size() << endl;
            cout << "Semester: " << uSemester.size() << endl;
            cout << "Course Code: " << uCourse_Code.size() << endl;
            cout << "Marks: " << uMarks.size() << endl;
            cout << "Discipline: " << udiscipline.size() << endl;

            cout << endl;

            cout << "Number of null values for each column in Course data:" << endl;
            cout << "Student ID: " << idnull << endl;
            cout << "Degree: " << degreenull << endl;
            cout << "Semester: " << semnull << endl;
            cout << "Course Code: " << codenull << endl;
            cout << "Marks: " << marksnull << endl;
            cout << "Discipline: " << disciplinenull << endl;

            cout << endl << "Total Courses: " <<uCourse_Code.size() << endl;


            cout << endl << "Total no. of female students Vs male students: " << female << ":" << male << endl;

            int result = countStudentsWithMoreThanFiveCourses(Cdata);

            cout << endl << "Students with more than 5 courses: " << result << endl;
            cout << endl << "Total no. of unique student IDs Vs total students: " << uSID.size() << ":" << Sdata.size() << endl;



            break;
        }

        case 2: //Peshawar statistics calculated and printed on screen
        {
            set <string> uSID;
            set <string> uDegree;
            set <string> uSemester;
            set <string> uCourse_Code;
            set <string> uMarks;
            set <string> udiscipline;
            int idnull = 0, degreenull = 0, codenull = 0, marksnull = 0, disciplinenull = 0, semnull = 0;

            for (int i=0; i<PCdata.size(); i++){              // adds unique values into the set
                uSID.insert(PCdata[i].SID);                   // unique IDs added to uSID 
                uDegree.insert(PCdata[i].Degree);
                uCourse_Code.insert(PCdata[i].Course_Code);
                uMarks.insert(PCdata[i].Marks);
                udiscipline.insert(PCdata[i].discipline);
                uSemester.insert(PCdata[i].Semester);

                if (PCdata[i].SID.empty()){                 // checks for empty values
                    idnull++;
                }
                if (PCdata[i].Degree.empty()){
                    degreenull++;
                }
                if (PCdata[i].Semester.empty()){
                    semnull++;
                }
                if (PCdata[i].Course_Code.empty()){
                    codenull++;
                }
                if (PCdata[i].Marks.empty()){
                    marksnull++;
                }
                if (PCdata[i].discipline.empty()){
                    disciplinenull++;
                }
            }

            int mfratio =0, male=0, female=0;
            for (int i=0; i<PSdata.size(); i++){
                if (PSdata[i].Gender == "M"){
                    male++;
                }
                else if (PSdata[i].Gender == "F"){
                    female++;
                }
            }

            int morethanfive = 0;
            int coursescounter;
            string current = "";
            for (int i = 0; i < PCdata.size(); i++) {
                if (PCdata[i].SID == current) {
                    coursescounter++;
                } else {
                    current = PCdata[i].SID;
                    coursescounter = 1;
                }
                if (coursescounter > 5) {
                    morethanfive++;
                }
            }



            cout << "Number of unique values for each column in Course data:" << endl;
            cout << "Student ID: " << uSID.size() << endl;
            cout << "Degree: " << uDegree.size() << endl;
            cout << "Semester: " << uSemester.size() << endl;
            cout << "Course Code: " << uCourse_Code.size() << endl;
            cout << "Marks: " << uMarks.size() << endl;
            cout << "Discipline: " << udiscipline.size() << endl;

            cout << endl;

            cout << "Number of null values for each column in Course data:" << endl;
            cout << "Student ID: " << idnull << endl;
            cout << "Degree: " << degreenull << endl;
            cout << "Semester: " << semnull << endl;
            cout << "Course Code: " << codenull << endl;
            cout << "Marks: " << marksnull << endl;
            cout << "Discipline: " << disciplinenull << endl;

            cout << endl << "Total Courses: " <<uCourse_Code.size() << endl;


            cout << endl << "Total no. of female students Vs male students: " << female << ":" << male << endl;
            int result2 = countStudentsWithMoreThanFiveCourses(PCdata);

            cout << endl << "Students with more than 5 courses: " << result2 << endl;
            cout << endl << "Total no. of unique student IDs Vs total students: " << uSID.size() << ":" << PSdata.size() << endl;

            break;
        }


        case 3:
        {
            // unique values
            set<string> uSID;
            set<string> uDegree;
            set<string> uSemester;
            set<string> uCourse_Code;
            set<string> uMarks;
            set<string> udiscipline;
            int idnull = 0, degreenull = 0, codenull = 0, marksnull = 0, disciplinenull = 0, semnull = 0;

            for (int i = 0; i < ACdata.size(); i++)
            {                               // adds unique values into the set
                uSID.insert(ACdata[i].SID); // unique IDs added to uSID
                uDegree.insert(ACdata[i].Degree);
                uCourse_Code.insert(ACdata[i].Course_Code);
                uMarks.insert(ACdata[i].Marks);
                udiscipline.insert(ACdata[i].discipline);
                uSemester.insert(ACdata[i].Semester);

                if (ACdata[i].SID.empty())
                { // checks for empty values
                    idnull++;
                }
                if (ACdata[i].Degree.empty())
                {
                    degreenull++;
                }
                if (ACdata[i].Semester.empty())
                {
                    semnull++;
                }
                if (ACdata[i].Course_Code.empty())
                {
                    codenull++;
                }
                if (ACdata[i].Marks.empty())
                {
                    marksnull++;
                }
                if (ACdata[i].discipline.empty())
                {
                    disciplinenull++;
                }
            }

            set <string> PSemesters;
            for (int i=0; i<PCdata.size(); i++){
                PSemesters.insert(PCdata[i].Semester);

            }
            set <string> LSemesters;
            for (int i=0; i<Cdata.size(); i++){
                LSemesters.insert(Cdata[i].Semester);
            }
            

            // null student
            int sid = 0, add = 0, city = 0, deg = 0, fath = 0, gend = 0, lastd = 0, regd = 0, regs = 0, stname = 0, dob = 0;
            for (int i = 0; i < ASdata.size(); i++)
            { // adds unique values into the set

                if (ASdata[i].SID.empty())
                { // checks for empty values
                    sid++;
                }
                if (ASdata[i].Address.empty())
                {
                    add++;
                }
                if (ASdata[i].city_name.empty())
                {
                    city++;
                }
                if (ASdata[i].Degree_Status.empty())
                {
                    deg++;
                }
                if (ASdata[i].DOB.empty())
                {
                    dob++;
                }
                if (ASdata[i].Father_Name.empty())
                {
                    fath++;
                }
                if (ASdata[i].Gender.empty())
                {
                    gend++;
                }
                if (ASdata[i].Last_Degree.empty())
                {
                    lastd++;
                }
                if (ASdata[i].Reg_Date.empty())
                {
                    regd++;
                }
                if (ASdata[i].Reg_Status.empty())
                {
                    regs++;
                }
                if (ASdata[i].St_Name.empty())
                {
                    stname++;
                }
            }
            
            
            // male to female count
            int mfratio = 0, male = 0, female = 0;
            for (int i = 0; i < ASdata.size(); i++)
            {
                if (ASdata[i].Gender == "M")
                {
                    male++;
                }
                else if (ASdata[i].Gender == "F")
                {
                    female++;
                }
            }
        
            // more than 5 courses
            int result = countStudentsWithMoreThanFiveCourses(Cdata);
            int result2 = countStudentsWithMoreThanFiveCourses(PCdata);
            int morethanfive = result + result2;

            // lahore campus strength
            int LahoreSize = Sdata.size();
            int total_sems = LSemesters.size();
            int lahore_campus_strength = LahoreSize / total_sems;

            // peshawar strengh
            int PeshawarSize = PSdata.size();
            int total_Psems = PSemesters.size();
            int pesh_campus_strength = PeshawarSize/total_Psems;
            cout << "Number of unique values for each column in All Course data:" << endl;
            cout << "Student ID: " << uSID.size() << endl;
            cout << "Degree: " << uDegree.size() << endl;
            cout << "Semester: " << uSemester.size() << endl;
            cout << "Course Code: " << uCourse_Code.size() << endl;
            cout << "Marks: " << uMarks.size() << endl;
            cout << "Discipline: " << udiscipline.size() << endl;

            cout << endl;


            cout << "Number of null values for each column in All Course data:" << endl;
            cout << "Student ID: " << idnull << endl;
            cout << "Degree: " << degreenull << endl;
            cout << "Semester: " << semnull << endl;
            cout << "Course Code: " << codenull << endl;
            cout << "Marks: " << marksnull << endl;
            cout << "Discipline: " << disciplinenull << endl << endl;

            cout << "Number of null values for each column in All Student Data: " << endl;
            cout << "Student ID: " << sid << endl;
            cout << "Student Name: " << stname << endl;
            cout << "Address: " << add << endl;
            cout << "City: " << city << endl;
            cout << "Degree Status: " << deg << endl;
            cout << "Date of Birth: " << dob << endl;
            cout << "Father's Name: " << fath << endl;
            cout << "Gender: " << gend << endl;
            cout << "Last Degree: " << lastd << endl;
            cout << "Registration Date: " << regd << endl;
            cout << "Registration Status: " << regs << endl;


            cout << endl;

            cout << endl << "Total Courses: " <<uCourse_Code.size() << endl;


            cout << endl << "Total no. of female students Vs male students: " << female << ":" << male << endl;


            cout << endl << "Students with more than 5 courses: " << morethanfive << endl;
            cout << endl << "Total no. of unique student IDs Vs total students: " << uSID.size() << ":" << ASdata.size() << endl;

            cout << endl;
            cout << "Average number of people per semester in Lahore campus: " << lahore_campus_strength << endl;
            cout << "Average number of people per semester in Peshawar campus: " << pesh_campus_strength;

            cout << endl;
            cout << "Average number of people per batch in Lahore campus: " << Sdata.size()/12 << endl;
            cout << "Average number of people per batch in Peshawar campus: " << PSdata.size()/11 ;
            break;

        }

        default:
        {
            cout<<"Invalid entry...";
            return 0;
            break;
        }


    }
    return 0;
}