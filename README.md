# High-Performance Linear Algebra: class materials

## Syllabus

CU Boulder: CSCI 4830-801/7000-003(B) (Spring 2017)

Meeting Time: MW 3:0-4:15pm in ECCS 1B14

Instructor: [Jed Brown](https://jedbrown.org), [<tt>jed.brown@colorado.edu</tt>](mailto:jed.brown@colorado.edu), ECOT 621
Office Hours: M 1-2pm, T 2-3:15pm, W 10-11am, or by appointment.  I will occasionally need to reschedule an office hour and will maintain a current calendar on this website.

### Overview

Covers algorithm development, optimization, and libraries for computational linear algebra on laptops to supercomputers. Includes techniques for sparse and hierarchical matrices, linear solvers, eigensolvers, and applications ranging from PDE and integral equations, data assimilation, control systems, and machine learning.

### Organization

Precise topics and applications will be tuned to the interests and preparation of students.  We will start with some common algorithms and patterns in direct linear algebra for dense and sparse matrices. Though robust, these methods have poor algorithmic scaling, thus motivating a transition to iterative methods. Fast convergence of iterative methods depends on scalable preconditioning, typically in the form of multilevel methods. These methods are typically associated with sparse matrices, but are also useful for “data sparse” representations of dense operators, such as arise in integral equations. Applications will be mixed in throughout, with more diversity and emphasis towards the end. Throughout the course, we will discuss practical aspects of parallel programming and performance analysis.

### Benefits

Many problems in computational science and engineering as well as machine learning have a performance bottleneck in linear algebra or related algorithms.
Upon completing this course, students possess an ability to

* formulate problems in science and engineering in terms of linear algebra
* optimize implementations of linear algebraic algorithms for multi-core and distributed memory architectures
* recognize and exploit structure to apply algorithms that improve performance and scalability
* understand the merits and limitations of linear algebraic techniques and implementations
* select and use robust software libraries
* develop effective numerical software, taking into account stability, accuracy, and cost
* predict scaling challenges and computational costs when solving increasingly complex problems or attempting to meet real-time requirements
* interpret research papers and begin research in the field

### Evaluation

* 40% class participation and contribution to homework.  There will be about 8 homework assignments that will involve some software development and numerical experiments.
* 30% final project.  A one-page written proposal is due April 17 and the project (code + write-up) is due on May 10.  I'll help you find a suitable project.
* Two midterms of 15% each, to be held in-class March 1 and April 5.

Assignments will be submitted by pull request on GitHub.  Join the class organization here:

https://classroom.github.com/classrooms/25191384-cu-boulder-computer-science-high-performance-linear-algebra

The grade for coding assignments will be a combination of pure
correctness, code cleanliness, and efficiency/scalability. It is
notoriously difficult to predict the time required to produce quality
code, so please start early to give yourself plenty of time.

You are encouraged to work together on all assignments, but must give
credit to peer contributions via the commit messages or Git history. For
example, you would add

    Suggested-by: Friendly Neighbor <friendly.neighbor@colorado.edu>

to the commit message if that code incorporates an approach suggested by
your neighbor.  Alternatively, you can `merge` or `cherry-pick` a commit
written by your peer (these operations preserve author information). You
should ensure that each assignment (pull request) contains some of your
own meaningful intellectual contributions.

### Programming languages and environment

Production numerical software is most frequently written in C, C++, or
Fortran, perhaps called from a higher level programming language.  Any
language is allowed for your own work, but I recommend one of the above
due to its mature tool support on HPC architectures.  We may sometimes
use Python to demonstrate algorithmic properties in an interactive
environment.  Most HPC facilities use a Linux operating system.  You can
use any environment for your local development environment, but the
[CS virtual machine](https://foundation.cs.colorado.edu/vm/) is
recommended if you encounter problems.  I will assist with access and
usage when we run experiments on HPC machines.

### Target audience

Advanced undergraduate and graduate students in computer science or simulation-based science or engineering.  We assume familiarity with a compiled language (e.g., C or Fortran) and Unix/Linux development environment, but prior experience with parallel computing is not essential.  Suggested prereq: at least one of

* CSCI-3656 Numerical Computation
* CSCI-4576 High-Performance Scientific Computing
* Undergrad enrollment by permission

### Resources (updated continuously)

* https://bitbucket.org/VictorEijkhout/hpc-book-and-course/src
* https://github.com/flame/blislab

### Disability Accommodations

If you qualify for accommodations because of a disability, please submit to your
professor a letter from Disability Services in a timely manner (for exam
accommodations provide your letter at least one week prior to the exam) so that
your needs can be addressed. Disability Services determines accommodations
based on documented disabilities. Contact Disability Services at 303-492-8671 or by
e-mail at dsinfo@colorado.edu. If you have a temporary medical condition or injury,
see the Temporary Injuries guidelines under the Quick Links at the Disability
Services website and discuss your needs with your professor.

### Religious Observances

[Campus policy regarding religious observances](http://www.colorado.edu/policies/fac_relig.html)
requires that faculty make every effort to deal reasonably and fairly
with all students who, because of religious obligations, have conflicts
with scheduled exams, assignments or required assignments/attendance. If
this applies to you, please speak with me directly as soon as possible
at the beginning of the term. See the
[campus policy regarding religious observances](http://www.colorado.edu/policies/observance-religious-holidays-and-absences-classes-andor-exams)
for full details.

### Classroom Behavior

Students and faculty each have responsibility for maintaining an
appropriate learning environment. Those who fail to adhere to such
behavioral standards may be subject to discipline. Professional courtesy
and sensitivity are especially important with respect to individuals and
topics dealing with differences of race, color, culture, religion,
creed, politics, veteran's status, sexual orientation, gender, gender
identity and gender expression, age, disability,and nationalities. Class
rosters are provided to the instructor with the student's legal name. I
will gladly honor your request to address you by an alternate name or
gender pronoun. Please advise me of this preference early in the
semester so that I may make appropriate changes to my records. For more
information, see the policies on
[classroom behavior](http://www.colorado.edu/policies/student-classroom-and-course-related-behavior)
and the
[student code](http://www.colorado.edu/osc/sites/default/files/attached-files/studentconductcode_16-17-a.pdf).

### Discrimination and Harassment

The University of Colorado Boulder (CU Boulder) is committed to maintaining a
positive learning, working, and living environment. CU Boulder will not tolerate acts
of sexual misconduct, discrimination, harassment or related retaliation against or by
any employee or student. CU's Sexual Misconduct Policy prohibits sexual assault,
sexual exploitation, sexual harassment,intimate partner abuse (dating or domestic
violence), stalking or related retaliation. CU Boulder's Discrimination and
Harassment Policy prohibits discrimination, harassment or related retaliation based
on race, color,national origin, sex, pregnancy, age, disability, creed, religion, sexual
orientation, gender identity, gender expression, veteran status, political affiliation or
political philosophy. Individuals who believe they have been subject to misconduct
under either policy should contact the Office of Institutional Equity and Compliance
(OIEC) at 303-492-2127. Information about the OIEC, the above referenced policies,
and the campus resources available to assist individuals regarding sexual
misconduct, discrimination, harassment or related retaliation can be found at the
[OIEC website](http://www.colorado.edu/institutionalequity/).

### Honor Code

All students enrolled in a University of Colorado Boulder course are
responsible for knowing and adhering to the
[academic integrity policy](http://www.colorado.edu/policies/academic-integrity-policy)
of the institution. Violations of the policy may include: plagiarism,
cheating,fabrication, lying, bribery, threat, unauthorized access,
clicker fraud,resubmission, and aiding academic dishonesty.  All
incidents of academic misconduct will be reported to the Honor Code
Council (honor@colorado.edu; 303-735-2273). Students who are found
responsible for violating the academic integrity policy will be subject
to nonacademic sanctions from the Honor Code Council as well as academic
sanctions from the faculty member. Additional information regarding the
academic integrity policy can be found at http://honorcode.colorado.edu.
