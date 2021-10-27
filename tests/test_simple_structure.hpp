//
// Created by rudi on 27/10/21.
//

#ifndef TEST_SIMPLE_STRUCTURE_HPP
#define TEST_SIMPLE_STRUCTURE_HPP

#define NAME_LENGTH 30

extern "C" {
	#include <serialize_buffer.h>
};

namespace {
class SimpleStructureTest : public ::testing::Test {
protected:
	typedef struct person_t {
		char name[NAME_LENGTH];
		int age;
		int weight;
	} Person;

	void serializedPerson(Person *person, SerializeBuffer *buffer) {
		if (!person) {
			serialize_buffer_serialize(buffer, (char *) SENTINEL_VALUE, sizeof(person));
			return;
		}

		serialize_buffer_serialize(buffer, (char *) person->name, sizeof(char) * NAME_LENGTH);
		serialize_buffer_serialize(buffer, (char *) &person->age, sizeof(int));
		serialize_buffer_serialize(buffer, (char *) &person->weight, sizeof(int));
		serialize_buffer_reset(buffer);
	}

	void deSerializePerson(Person *person, SerializeBuffer *buffer) {
		serialize_buffer_deserialize(buffer, person->name, sizeof(char) * NAME_LENGTH);
		serialize_buffer_deserialize(buffer, (char *) &person->age, sizeof(int));
		serialize_buffer_deserialize(buffer, (char *) &person->weight, sizeof(int));
	}
};
};

TEST_F(SimpleStructureTest, SerializedPerson) {
	Person personSrc, personDest;
	SerializeBuffer *buffer;

	memset(&personSrc, 0, sizeof(personSrc));
	memset(&personSrc, 0, sizeof(personSrc));

	serialize_buffer_init(&buffer);

	strcpy(personSrc.name, "David Andrew");
	personSrc.age = 30;
	personSrc.weight = 65;

	serializedPerson(&personSrc, buffer);
	deSerializePerson(&personDest, buffer);

	ASSERT_EQ(strcmp(personDest.name, personSrc.name), 0);
	ASSERT_EQ(personDest.age, 30);
	ASSERT_EQ(personDest.weight, 65);
}

#endif // TEST_SIMPLE_STRUCTURE_HPP
