class StudentInfo:

    def __init__(self) -> None:
        self.db = {}

    def add_course(self, course, grade):
        self.db[course] = grade
    
    def print_grades(self):
        print("all grades:")
        for key in self.db:
            print(key, '\t', self.db[key], sep="")

    def average(self):
        sum = 0
        print('average grade: ', end = "")
        for key in self.db:
            sum += self.db[key]
        print('{0:.2f}'.format((sum / len(self.db))))

    def fail(self):
        print('failed courses:')
        for key in self.db:
            if self.db[key] < 4:
                print(key)


info_class = StudentInfo()

while True:
    com = input("command: ")
    com = com.lower()
    if com == 'add':
        info_class.add_course(input("input course:"), int(input("input grade: ")))
    elif com == 'print':
        info_class.print_grades()
    elif com == 'average':
        info_class.average()
    elif com == 'fail':
        info_class.fail()
    elif com == 'done':
        break
print("DONE")