#include <string>

using namespace std;

struct Course {
  string value;

  explicit Course(string v) { value = v; }
};

struct Week {
  string value;

  explicit Week(string v) { value = v; }
};

struct Specialization {
  string value;

  explicit Specialization(string v) { value = v; }
};

struct LectureTitle {
  string specialization;
  string course;
  string week;

  LectureTitle(Specialization s, Course c, Week w) {
    specialization = s.value;
    course = c.value;
    week = w.value;
  }
};
