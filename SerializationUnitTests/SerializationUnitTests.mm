//
//  SerializationUnitTests.mm
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 13/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include "StdStream.hpp"
#include "BinaryCoder.hpp"
#include "TextCoder.hpp"
#include "XMLCoder.hpp"
#include "NoPointerPolicy.hpp"
#include "RebuildPointerPolicy.hpp"
#include "RebindPointerPolicy.hpp"
#include "StdContainer.hpp"
#include "StdString.hpp"
#include "StdSmartPtr.hpp"
#include "ClassSimpleData.hpp"
#include "ClassComposition.hpp"
#include "ClassPointerSameAddressTypes.hpp"
#include "ClassPointerNew.hpp"
#include "ClassPointerInside.hpp"
#include "ClassPointerOutside.hpp"
#include "ClassPointerItself.hpp"
#include "ClassPointerHierarchy.hpp"
#include "ClassPointerCycle.hpp"
#include "ClassPointerTwoRelated.hpp"
#include "ClassVersioning.hpp"
#include "ClassNoDefaultConstructor.hpp"
#include "ClassParentChild.hpp"
//TODO: tester une classe de base avec des données a serializer et une classe dérivée avec aussi des données a serializer, voir si ca se combine avec les données parent dans la classe fille

@interface SerializationUnitTests : XCTestCase {
    Serializer<StdOstream, /*XMLEncoder*/BinaryEncoder, RebuildPointerEncodePolicy/*NoPointerPolicy*//*RebindPointerEncodePolicy*/> *serializer;
    Deserializer<StdIstream, /*XMLDecoder*/BinaryDecoder, RebuildPointerDecodePolicy/*NoPointerPolicy*//*RebindPointerDecodePolicy*/> *deserializer;
    std::ifstream istream;
    std::ofstream ostream;
}

@end

@implementation SerializationUnitTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    // Le path est /private/tmp pour les tests
    ostream.open("file.txt");
    serializer = new Serializer<StdOstream, /*XMLEncoder*/BinaryEncoder, RebuildPointerEncodePolicy/*NoPointerPolicy*//*RebindPointerEncodePolicy*/>(ostream);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)terminateSerializationAndStartDeserialization {
    delete serializer;
    ostream.close();
    
    // TODO: obligé de le mettre la sinon si on le met a la definition, ca va bugger si le fichier n'existe pas encore (il va lire des données fausses !!!)
    istream.open("file.txt");
    deserializer = new Deserializer<StdIstream, /*XMLDecoder*/BinaryDecoder, RebuildPointerDecodePolicy/*NoPointerPolicy*//*RebindPointerDecodePolicy*/>(istream);
}

- (void)terminateDeserialization {
    delete deserializer;
    istream.close();
}

- (void)testSerializationNoPointer {
    ClassSimpleData classSimpleData(true, 'x', 1, 2, 3, 4, 5.1f, 6.2, 7.3);
    serializer->encode(classSimpleData);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassSimpleData classSimpleDataCopy;
    deserializer->decode(classSimpleDataCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classSimpleData == classSimpleDataCopy);
}

- (void)testSerializationComposition {
    ClassComposition classComposition(true, ClassSimpleData(true, 'x', 1, 2, 3, 4, 5.1f, 6.2, 7.3), 8);
    serializer->encode(classComposition);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassComposition classCompositionCopy;
    deserializer->decode(classCompositionCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classComposition == classCompositionCopy);
}

- (void)testSerializationPointerSameAddressTypes {
    ClassSimpleData classSimpleData(true, 'x', 1, 2, 3, 4, 5.1f, 6.2, 7.3);
    ClassPointerSameAddressTypes classPointerSameAddressTypes(&classSimpleData, &classSimpleData._boolValue);
    
    serializer->encode(classSimpleData);
    serializer->encode(classPointerSameAddressTypes);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassSimpleData classSimpleDataCopy;
    deserializer->decode(classSimpleDataCopy);
    
    ClassPointerSameAddressTypes classPointerSameAddressTypesCopy;
    deserializer->decode(classPointerSameAddressTypesCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classSimpleData == classSimpleDataCopy);
    XCTAssertTrue(classPointerSameAddressTypes == classPointerSameAddressTypesCopy);
}

- (void)testSerializationPointerToNew {
    ClassPointerNew classPointerNew(new int(2));
    serializer->encode(classPointerNew);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerNew classPointerNewCopy(new int(0));
    deserializer->decode(classPointerNewCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerNew == classPointerNewCopy);
}

- (void)testSerializationPointerToNull {
    ClassPointerNew classPointerNew(nullptr);
    serializer->encode(classPointerNew);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerNew classPointerNewCopy(new int(3));
    deserializer->decode(classPointerNewCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerNew == classPointerNewCopy);
}

- (void)testSerializationPointerToStaticInside {
    ClassPointerInside classPointerInside(6);
    serializer->encode(classPointerInside);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerInside classPointerInsideCopy(0);
    deserializer->decode(classPointerInsideCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerInside == classPointerInsideCopy);
}

- (void)testSerializationPointerToStaticOutside {
    int data = 2;
    ClassPointerOutside classPointerOutside(6, &data);
    serializer->encode(classPointerOutside);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerOutside classPointerOutsideCopy(0, &data);
    deserializer->decode(classPointerOutsideCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerOutside == classPointerOutsideCopy);
}

- (void)testSerializationPointerToItself1 {
    // Two way to achieve this, first is the best, simply don't serialize the pointer and set/reconstruct it in the constructor / assignment operator
    ClassPointerItself classPointerItself(7, &classPointerItself);
    serializer->encode(classPointerItself);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerItself classPointerItselfCopy(0, &classPointerItselfCopy);
    deserializer->decode(classPointerItselfCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerItself == classPointerItselfCopy);
}

- (void)testSerializationPointerToItself2 {
    // Second is to serialize it, Serialization library will recognize that object pointed is already deserialized and no infinite loop will happen
    ClassPointerItself2 classPointerItself2(7, &classPointerItself2);
    serializer->encode(classPointerItself2);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerItself2 classPointerItself2Copy(0, nullptr);
    deserializer->decode(classPointerItself2Copy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerItself2 == classPointerItself2Copy);
}

- (void)testSerializationPointerHierarchy {
    ClassPointerHierarchy classPointerHierarchy(8, new ClassPointerHierarchy(10, new ClassPointerHierarchy(12, nullptr, false), true), true);
    serializer->encode(classPointerHierarchy);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerHierarchy classPointerHierarchyCopy(0, nullptr, false);
    deserializer->decode(classPointerHierarchyCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerHierarchy == classPointerHierarchyCopy);
}

- (void)testSerializationPointerCycle {
    ClassPointerCycle classPointerCycle(14, new ClassPointerCycle2(16, &classPointerCycle));
    
    serializer->encode(classPointerCycle);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerCycle classPointerCycleCopy(0, nullptr);
    deserializer->decode(classPointerCycleCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerCycle == classPointerCycleCopy);
}

- (void)testSerializeTwoObjectsUnrelated {
    ClassSimpleData classSimpleData1(true, 'x', 1, 2, 3, 4, 5.1f, 6.2, 7.3);
    ClassSimpleData classSimpleData2(false, 'y', 2, 3, 4, 5, 6.1f, 7.2, 8.3);
    serializer->encode(classSimpleData1);
    serializer->encode(classSimpleData2);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassSimpleData classSimpleData1Copy;
    ClassSimpleData classSimpleData2Copy;
    deserializer->decode(classSimpleData1Copy);
    deserializer->decode(classSimpleData2Copy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classSimpleData1 == classSimpleData1Copy);
    XCTAssertTrue(classSimpleData2 == classSimpleData2Copy);
}

- (void)testVersioning {
    ClassVersioning classVersioning0(0, true, 34);
    ClassVersioning classVersioning1(1, true, 35);
    serializer->encode(classVersioning0);
    serializer->encode(classVersioning1, "", 1);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassVersioning classVersioning0Copy;
    ClassVersioning classVersioning1Copy;
    deserializer->decode(classVersioning0Copy);
    deserializer->decode(classVersioning1Copy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classVersioning0 == classVersioning0Copy);
    XCTAssertTrue(classVersioning1 == classVersioning1Copy);
}

- (void)testSerializeTwoObjectsRelated {//TODO: pour que ca fonctionne correctement, il faut la RebindPointerPolicy (avec RebuildPointerPolicy, il va créer un objet de trop)
    ClassPointerTwoRelated classPointerTwoRelated(20, nullptr);
    ClassPointerTwoRelated2 classPointerTwoRelated2(22, &classPointerTwoRelated);
    classPointerTwoRelated.setPointer(&classPointerTwoRelated2);
    
    serializer->encode(classPointerTwoRelated);
    serializer->encode(classPointerTwoRelated2);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassPointerTwoRelated classPointerTwoRelatedCopy(0, nullptr);
    ClassPointerTwoRelated2 classPointerTwoRelated2Copy(0, nullptr);
    std::cout << &classPointerTwoRelatedCopy << std::endl;
    std::cout << &classPointerTwoRelated2Copy << std::endl;
    deserializer->decode(classPointerTwoRelatedCopy);
    deserializer->decode(classPointerTwoRelated2Copy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classPointerTwoRelated == classPointerTwoRelatedCopy);
    XCTAssertTrue(classPointerTwoRelated2 == classPointerTwoRelated2Copy);
}

- (void)testSerializeStdArrayInt {
    std::array<int, 4> aint = { 23, 25, 26, 27 };
    
    serializer->encode(aint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::array<int, 4> aintCopy = { 0, 0, 0, 0 };
    deserializer->decode(aintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(aint == aintCopy);
}

- (void)testSerializeStdArrayDeserializeVectorInt {
    std::array<int, 4> aint = { 23, 25, 26, 27 };
    
    serializer->encode(aint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::vector<int> vintCopy;
    deserializer->decode(vintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(std::equal(aint.begin(), aint.end(), vintCopy.begin(), vintCopy.end()));
}

- (void)testSerializeStdVectorInt {
    std::vector<int> vint = { 23, 25, 26, 27 };
    
    serializer->encode(vint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::vector<int> vintCopy;
    deserializer->decode(vintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(vint == vintCopy);
}

- (void)testSerializeStdVectorClassWithoutDefaultConstructor {
    std::vector<ClassNoDefaultConstructor> vclass = { 23, 25, 26, 27 };
    
    serializer->encode(vclass);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::vector<ClassNoDefaultConstructor> vclassCopy;
    deserializer->decode(vclassCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(vclass == vclassCopy);
}

- (void)testSerializeStdDequeInt {
    std::deque<int> dint = { 34, 35, 36, 37, 38 };
    
    serializer->encode(dint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::deque<int> dintCopy;
    deserializer->decode(dintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(dint == dintCopy);
}

- (void)testSerializeStdForwardListInt {
    std::forward_list<int> flint = { 34, 35, 36, 37, 38 };
    
    serializer->encode(flint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::forward_list<int> flintCopy;
    deserializer->decode(flintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(flint == flintCopy);
}

- (void)testSerializeStdListInt {
    std::list<int> lint = { 44, 45, 46, 47, 48 };
    
    serializer->encode(lint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::list<int> lintCopy;
    deserializer->decode(lintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(lint == lintCopy);
}

- (void)testSerializeStdSetInt {
    std::set<int> sint = { 54, 55, 56, 57, 58 };
    
    serializer->encode(sint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::set<int> sintCopy;
    deserializer->decode(sintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(sint == sintCopy);
}

- (void)testSerializeStdMapInt {
    std::map<int, int> mint = { { 1, 30 }, { 2, 31 }, { 3, 32 } };
    
    serializer->encode(mint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::map<int, int> mintCopy;
    deserializer->decode(mintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(mint == mintCopy);
}

- (void)testSerializeStdUnorderedSetInt {
    std::unordered_set<int> usint = { 54, 55, 56, 57, 58 };
    
    serializer->encode(usint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::unordered_set<int> usintCopy;
    deserializer->decode(usintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(usint == usintCopy);
}

- (void)testSerializeStdUnorderedMapInt {
    std::unordered_map<int, int> umint = { { 1, 30 }, { 2, 31 }, { 3, 32 } };
    
    serializer->encode(umint);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::unordered_map<int, int> umintCopy;
    deserializer->decode(umintCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(umint == umintCopy);
}

- (void)testSerializeStdString {
    std::string str = "Hello world\nMultiline !\n";
    
    serializer->encode(str);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::string strCopy;
    deserializer->decode(strCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(str == strCopy);
}

- (void)testSerializeString {
    int a = 10, b = 20;
    char const *str = "Hello world\nMultiline !\n";
    
    serializer->encode(a);
    serializer->encode(str);
    serializer->encode(b);
    
    [self terminateSerializationAndStartDeserialization];
    
    int a2 = 0, b2 = 0;
    //char strCopy[32];
    char *strCopy = nullptr;
    deserializer->decode(a2);
    deserializer->decode(strCopy);//TODO: passer un pointer sur nullptr et l'allocation se fait coté serializer ?, passer un pointeur deja alloué (mais comment savoir la taille ?) A voir, c'est le meme probleme que pour les pointeurs et les arrays
    deserializer->decode(b2);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(a == a2);
    XCTAssertTrue(strcmp(str, strCopy) == 0);
    XCTAssertTrue(b == b2);
    
    //delete [] strCopy;
    std::free(strCopy);
}

- (void)testSerializeArrayIntFixedSize {
    int aint[] = { 60, 61, 62, 63, 64 };
    std::size_t size = sizeof(aint) / sizeof(aint[0]);
    
    serializer->encode(aint, size);
    
    [self terminateSerializationAndStartDeserialization];
    
    int *aint2 = new int[size];    // User decoding code known the size of the encoded array (to size the decoding array)
    std::size_t size2;
    deserializer->decode(aint2, size2);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(size == size2);
    for (std::size_t i = 0; i < size; ++i) {
        XCTAssertTrue(aint[i] == aint2[i]);
    }
    
    delete [] aint2;
}

- (void)testSerializeArrayIntDynamicSize {
    int aint[] = { 60, 61, 62, 63, 64 };
    std::size_t size = sizeof(aint) / sizeof(aint[0]);
    
    serializer->encode(aint, size);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::size_t size2;
    deserializer->decode(size2, "size");
    XCTAssertTrue(size == size2);
    
    int *aint2 = new int[size2];
    for (std::size_t i = 0; i < size2; ++i) {
        deserializer->decode(aint2[i]);
    }
    
    [self terminateDeserialization];
    
    for (std::size_t i = 0; i < size2; ++i) {
        XCTAssertTrue(aint[i] == aint2[i]);
    }
    
    delete [] aint2;
}
/*
 - (void)testSerializeArrayDeserializeVectorInt {    // TODO: ne fonctionne pas avec XMLCoder car on encode comme data et on decode comme object
    int aint[] = { 60, 61, 62, 63, 64 };
    std::size_t size = sizeof(aint) / sizeof(aint[0]);
    
    serializer->encode(0);              // Need to fake encode version because array has no version and std::vector has a version
    serializer->encode(aint, size);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::vector<int> aint2;
    deserializer->decode(aint2);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(size == aint2.size());
    for (std::size_t i = 0; i < size; ++i) {
        XCTAssertTrue(aint[i] == aint2[i]);
    }
}*/

- (void)testPointerOfPointer {
    int value = 5;
    int *pValue = &value;
    int **ppValue = &pValue;
    
    serializer->encode(value);
    serializer->encode(pValue);
    serializer->encode(ppValue);
    
    [self terminateSerializationAndStartDeserialization];
    
    int valueCopy;
    int *pValueCopy;
    int **ppValueCopy;
    deserializer->decode(valueCopy);
    deserializer->decode(pValueCopy);
    deserializer->decode(ppValueCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(**ppValue == **ppValueCopy);
}

- (void)testArrayPointerOwners {
    int * aPOInt[4];
    int * aPOIntCopy[4];
    std::size_t size = 4;
    
    for (std::size_t i = 0; i < size; ++i) {
        aPOInt[i] = new int(static_cast<int>(i));
        aPOIntCopy[i] = new int(0);
    }
    
    // Need to encode and mark owner manually
    serializer->encode(size, "size");
    
    for (std::size_t i = 0; i < size; ++i) {
        serializer->encode(*aPOInt[i]);
    }
    
    [self terminateSerializationAndStartDeserialization];
    
    // Need to decode and mark owner manually
    std::size_t size2;
    deserializer->decode(size2, "size");
    XCTAssertTrue(size2 == size);
    
    for (std::size_t i = 0; i < size; ++i) {
        deserializer->decode(*aPOIntCopy[i]);
    }
    
    [self terminateDeserialization];
    
    for (std::size_t i = 0; i < size; ++i) {
        XCTAssertTrue(*aPOInt[i] == *aPOIntCopy[i]);
    }
    
    for (std::size_t i = 0; i < size; ++i) {
        delete aPOInt[i];
        delete aPOIntCopy[i];
    }
}/*
- (void)testArrayPointerOwners {
    int *aPOInt[4];
    int *aPOIntCopy[4];
    
    for (std::size_t i = 0; i < 4; ++i) {
        aPOInt[i] = new int(static_cast<int>(i));
        aPOIntCopy[i] = new int(0);
    }
    
    serializer->encode(MarkOwner(aPOInt), 4);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::size_t size2;
    deserializer->decode(MarkOwner(aPOIntCopy), size2);
  
    [self terminateDeserialization];
  
    XCTAssertTrue(size2 == 4);
    
    for (std::size_t i = 0; i < 4; ++i) {
        XCTAssertTrue(*aPOInt[i] == *aPOIntCopy[i]);
    }
}*/

- (void)testUniquePtr {
    std::unique_ptr<int> pInt(new int(21));
    serializer->encode(pInt);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::unique_ptr<int> pIntCopy(new int(0));
    deserializer->decode(pIntCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(*pInt == *pIntCopy);
}

- (void)testUniquePtrNull {
    std::unique_ptr<int> pInt(nullptr);
    serializer->encode(pInt);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::unique_ptr<int> pIntCopy(new int(0));
    deserializer->decode(pIntCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(pIntCopy == nullptr);
}
/*
- (void)testWeakPtr {
    std::shared_ptr<int> sptr(new int(35));
    std::weak_ptr<int> wptr = sptr;
    serializer->encode(MarkOwner(sptr.get()));
    serializer->encode(wptr);
    
    [self terminateSerializationAndStartDeserialization];
    
    std::shared_ptr<int> sptrCopy(new int(0));
    deserializer->decode(MarkOwner(sptrCopy.get()));
    std::weak_ptr<int> wptrCopy = sptrCopy;
    //deserializer->decode(wptrCopy);
 
    [self terminateDeserialization];
    
    XCTAssertTrue(*wptrCopy.lock().get() == 35);
}
*/

- (void)testClassParentChild {
    ClassChild classChild(true, 56);
    serializer->encode(classChild);
    
    [self terminateSerializationAndStartDeserialization];
    
    ClassChild classChildCopy;
    deserializer->decode(classChildCopy);
    
    [self terminateDeserialization];
    
    XCTAssertTrue(classChild == classChildCopy);
}

- (void)testClassParentChildAbstract {
    ClassChild classChild(true, 56);
    ClassParent *classParent = &classChild;
    
    // Pour serializer un objet polymorphique via un pointeur de base, il faut encoder manuellement un id pour permettre de savoir de quelle classe exacte est l'objet pour le deserializer
    if (typeid(*classParent) == typeid(ClassChild)) {
        serializer->encode(1);
        serializer->encode(dynamic_cast<ClassChild *>(classParent));
    } else {
        serializer->encode(0);
    }
    
    [self terminateSerializationAndStartDeserialization];
    
    int idClass;
    ClassParent *classParentCopy;
    deserializer->decode(idClass);
    
    if (idClass == 1) {
        ClassChild *classChildCopy;
        deserializer->decode(classChildCopy);
        
        classParentCopy = classChildCopy;
    }
    
    [self terminateDeserialization];
    
    XCTAssertTrue(*dynamic_cast<ClassChild *>(classParent) == *dynamic_cast<ClassChild *>(classParentCopy));
}

// + smart ptr, + pointers calculés (int *array; int *p = &array[2]; !!!

@end
