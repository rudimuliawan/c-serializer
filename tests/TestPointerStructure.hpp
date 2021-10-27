//
// Created by rudi on 27/10/21.
//

#ifndef TEST_POINTER_STRUCTURE
#define TEST_POINTER_STRUCTURE

#define NAME_LENGTH 30

extern "C" {
    #include <serialize_buffer.h>
};

namespace {
class PointerStructureTest : public ::testing::Test {
protected:
    typedef struct occupation_t {
        char dept_name[NAME_LENGTH];
        int employee_code;
    } Occupation;

    typedef struct person_t {
        char name[NAME_LENGTH];
        int age;
        Occupation *occupation;
        int weight;
    } Person;

    void serializedOccupation(Occupation *occupation, SerializeBuffer *buffer)
    {
        if (!occupation) {
            serialize_buffer_serialize(buffer, (char *) SENTINEL_VALUE, sizeof(occupation));
            return;
        }

        serialize_buffer_serialize(buffer, (char *) occupation->dept_name, sizeof(char) * NAME_LENGTH);
        serialize_buffer_serialize(buffer, (char *) &occupation->employee_code, sizeof(int));
    }

    void deserializedOccupation(Occupation *occupation, SerializeBuffer *buffer)
    {
        serialize_buffer_deserialize(buffer, (char *) occupation->dept_name, sizeof(char) * NAME_LENGTH);
        serialize_buffer_deserialize(buffer, (char *) &occupation->employee_code, sizeof(int));
    }

    void serializedPerson(Person *person, SerializeBuffer *buffer)
    {
        if (!person) {
            serialize_buffer_serialize(buffer, (char *) SENTINEL_VALUE, sizeof(person));
            return;
        }

        serialize_buffer_serialize(buffer, (char *) person->name, sizeof(char) * NAME_LENGTH);
        serialize_buffer_serialize(buffer, (char *) &person->age, sizeof(int));
        serializedOccupation(person->occupation, buffer);
        serialize_buffer_serialize(buffer, (char *) &person->weight, sizeof(int));

        serialize_buffer_seek_to_zero(buffer);
    }

    void deSerializePerson(Person *person, SerializeBuffer *buffer)
    {
        serialize_buffer_deserialize(buffer, person->name, sizeof(char) * NAME_LENGTH);
        serialize_buffer_deserialize(buffer, (char *) &person->age, sizeof(int));

        Occupation *occupation = (Occupation *)malloc(sizeof(Occupation));
        person->occupation = occupation;

        deserializedOccupation(person->occupation, buffer);
        serialize_buffer_deserialize(buffer, (char *) &person->weight, sizeof(int));
    }
};
};

TEST_F(PointerStructureTest, SerializedPerson)
{
    Person personSrc, personDest;
    Occupation occupation;
    SerializeBuffer *buffer;

    memset(&personSrc, 0, sizeof(personSrc));
    memset(&personDest, 0, sizeof(personDest));
    memset(&occupation, 0, sizeof(occupation));

    serialize_buffer_init(&buffer);

    strcpy(occupation.dept_name, "Finance");
    occupation.employee_code = 54;

    strcpy(personSrc.name, "David Andrew");
    personSrc.age = 30;
    personSrc.occupation = &occupation;
    personSrc.weight = 65;

    serializedPerson(&personSrc, buffer);

    deSerializePerson(&personDest, buffer);

    ASSERT_EQ(strcmp(personDest.name, personSrc.name), 0);
    ASSERT_EQ(personDest.age, 30);
    ASSERT_EQ(strcmp(personDest.occupation->dept_name, personSrc.occupation->dept_name), 0);
    ASSERT_EQ(personDest.occupation->employee_code, 54);
    ASSERT_EQ(personDest.weight, 65);
}

#endif // TEST_POINTER_STRUCTURE
