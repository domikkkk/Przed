CREATE TABLE activity (
    id                NUMBER(10) NOT NULL,
    description       VARCHAR2(255 CHAR),
    name              VARCHAR2(255 CHAR),
    student_can_trade CHAR(1)
);

ALTER TABLE activity ADD CONSTRAINT activity_pk PRIMARY KEY ( id );

CREATE TABLE "ACTIVITY LEADER" (
    teacher_id  INTEGER NOT NULL,
    activity_id NUMBER(10) NOT NULL
);

ALTER TABLE "ACTIVITY LEADER" ADD CONSTRAINT relation_21_pk PRIMARY KEY ( teacher_id,
                                                                          activity_id );

CREATE TABLE announcement (
    id         NUMBER(10) NOT NULL,
    headline   VARCHAR2(255 CHAR),
    info       VARCHAR2(255 CHAR),
    published  TIMESTAMP,
    teacher_id INTEGER
);

ALTER TABLE announcement ADD CONSTRAINT announcement_pk PRIMARY KEY ( id );

CREATE TABLE course_settings (
    id          NUMBER(10) NOT NULL,
    course_name VARCHAR2(255 CHAR),
    grade3      FLOAT(126),
    grade35     FLOAT(126),
    grade4      FLOAT(126),
    grade45     FLOAT(126),
    grade5      FLOAT(126)
);

ALTER TABLE course_settings ADD CONSTRAINT course_settings_pk PRIMARY KEY ( id );

CREATE TABLE exchange_offer (
    id              NUMBER(10) NOT NULL,
    info            VARCHAR2(255 CHAR),
    indeks NUMBER(10),
    market_id       NUMBER(10)
);

ALTER TABLE exchange_offer ADD CONSTRAINT exchange_offer_pk PRIMARY KEY ( id );

CREATE TABLE grade (
    id              NUMBER(10) NOT NULL,
    result          FLOAT(126),
    graded_test_id  NUMBER(10),
    indeks NUMBER(10),
    teacher_id      INTEGER
);

ALTER TABLE grade ADD CONSTRAINT grade_pk PRIMARY KEY ( id );

CREATE TABLE graded_test (
    id          NUMBER(10) NOT NULL,
    title       VARCHAR2(255 CHAR),
    max_points  FLOAT(126),
    test_date   DATE,
    activity_id NUMBER(10)
);

ALTER TABLE graded_test ADD CONSTRAINT graded_test_pk PRIMARY KEY ( id );

CREATE TABLE market (
    id NUMBER(10) NOT NULL
);

ALTER TABLE market ADD CONSTRAINT market_pk PRIMARY KEY ( id );

CREATE TABLE study_groups_offers (
    group_id   NUMBER(10) NOT NULL,
    offers_id NUMBER(10) NOT NULL
);

ALTER TABLE study_groups_offers ADD CONSTRAINT fk77sl2ix5dc50hpumpjpnsxref_pk PRIMARY KEY ( group_id,
                                                                                                 offers_id );

CREATE TABLE project (
    id              INTEGER NOT NULL,
    topic           VARCHAR2(255 CHAR),
    study_groups_id NUMBER(10)
);

ALTER TABLE project ADD CONSTRAINT project_pk PRIMARY KEY ( id );

CREATE TABLE "STUDENT PROJECT" (
    indeks NUMBER(10) NOT NULL,
    project_id      INTEGER NOT NULL
);

ALTER TABLE "STUDENT PROJECT" ADD CONSTRAINT relation_24_pk PRIMARY KEY ( indeks,
                                                                          project_id );

CREATE TABLE students (
    indeks    NUMBER(10) NOT NULL,
    birthdate DATE,
    firstname VARCHAR2(255 CHAR),
    lastname  VARCHAR2(255 CHAR),
    username  VARCHAR2(255 CHAR)
);

ALTER TABLE students ADD CONSTRAINT students_pk PRIMARY KEY ( indeks );

CREATE TABLE students_groups (
    indeks NUMBER(10) NOT NULL,
    id NUMBER(10) NOT NULL
);

ALTER TABLE students_groups ADD CONSTRAINT relation_18_pk PRIMARY KEY ( id,
                                                                              indeks );

CREATE TABLE study_groups (
    id          NUMBER(10) NOT NULL,
    group_size  NUMBER(10) NOT NULL,
    hour        NUMBER(10) NOT NULL,
    name        VARCHAR2(255 CHAR) NOT NULL,
    weekday     VARCHAR2(255 CHAR) NOT NULL,
    activity_id NUMBER(10)
);

ALTER TABLE study_groups ADD CONSTRAINT study_groups_pk PRIMARY KEY ( id );

CREATE TABLE teacher (
    id               INTEGER NOT NULL,
    username         VARCHAR2(255 CHAR),
    name             VARCHAR2(255 CHAR),
    surname          VARCHAR2(255 CHAR),
    scientific_title VARCHAR2(255 CHAR)
);

ALTER TABLE teacher ADD CONSTRAINT teacher_pk PRIMARY KEY ( id );

CREATE TABLE trade_period (
    id          NUMBER(10) NOT NULL,
    end_date    DATE,
    start_date  DATE,
    activity_id NUMBER(10)
);

ALTER TABLE trade_period ADD CONSTRAINT trade_period_pk PRIMARY KEY ( id );

ALTER TABLE announcement
    ADD CONSTRAINT announcement_teacher_fk FOREIGN KEY ( teacher_id )
        REFERENCES teacher ( id );

ALTER TABLE exchange_offer
    ADD CONSTRAINT exchange_offer_market_fk FOREIGN KEY ( market_id )
        REFERENCES market ( id );

ALTER TABLE exchange_offer
    ADD CONSTRAINT exchange_offer_students_fk FOREIGN KEY ( indeks )
        REFERENCES students ( indeks );

--  ERROR: FK name length exceeds maximum allowed length(30) 
ALTER TABLE study_groups_offers
    ADD CONSTRAINT fk77sl2ix5dc50hpumpjpnsxref_exchange_offer_fk FOREIGN KEY ( offers_id )
        REFERENCES exchange_offer ( id );

--  ERROR: FK name length exceeds maximum allowed length(30) 
ALTER TABLE study_groups_offers
    ADD CONSTRAINT fk77sl2ix5dc50hpumpjpnsxref_study_groups_fk FOREIGN KEY ( group_id )
        REFERENCES study_groups ( id );

ALTER TABLE grade
    ADD CONSTRAINT grade_graded_test_fk FOREIGN KEY ( graded_test_id )
        REFERENCES graded_test ( id );

ALTER TABLE grade
    ADD CONSTRAINT grade_students_fk FOREIGN KEY ( indeks )
        REFERENCES students ( indeks );

ALTER TABLE grade
    ADD CONSTRAINT grade_teacher_fk FOREIGN KEY ( teacher_id )
        REFERENCES teacher ( id );

ALTER TABLE graded_test
    ADD CONSTRAINT graded_test_activity_fk FOREIGN KEY ( activity_id )
        REFERENCES activity ( id );

ALTER TABLE project
    ADD CONSTRAINT project_study_groups_fk FOREIGN KEY ( id )
        REFERENCES study_groups ( id );

ALTER TABLE students_groups
    ADD CONSTRAINT relation_18_students_fk FOREIGN KEY ( indeks )
        REFERENCES students ( indeks );

ALTER TABLE students_groups
    ADD CONSTRAINT relation_18_study_groups_fk FOREIGN KEY ( id )
        REFERENCES study_groups ( id );

ALTER TABLE "ACTIVITY LEADER"
    ADD CONSTRAINT relation_21_activity_fk FOREIGN KEY ( activity_id )
        REFERENCES activity ( id );

ALTER TABLE "ACTIVITY LEADER"
    ADD CONSTRAINT relation_21_teacher_fk FOREIGN KEY ( teacher_id )
        REFERENCES teacher ( id );

ALTER TABLE "STUDENT PROJECT"
    ADD CONSTRAINT relation_24_project_fk FOREIGN KEY ( project_id )
        REFERENCES project ( id );

ALTER TABLE "STUDENT PROJECT"
    ADD CONSTRAINT relation_24_students_fk FOREIGN KEY ( indeks )
        REFERENCES students ( indeks );

ALTER TABLE study_groups
    ADD CONSTRAINT study_groups_activity_fk FOREIGN KEY ( activity_id )
        REFERENCES activity ( id );

ALTER TABLE trade_period
    ADD CONSTRAINT trade_period_activity_fk FOREIGN KEY ( activity_id )
        REFERENCES activity ( id );
