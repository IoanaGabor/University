//
// Created by ioana on 30.03.2023.
//

#include <cassert>
#include "TestRepository.h"
#include "repository/MemoryRepository.h"
#include "../domain/Event.h"

void TestRepository::testAddAndListElementsRepository() {
    MemoryRepository<Event> repository = MemoryRepository<Event>();
    repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafdds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    assert(repository.getAllEntities().size() == 4);
    try {
        repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
        assert(false);
    } catch (RepositoryException &repositoryException) {
        assert(true);
    }
}

void TestRepository::testRemoveRepository() {
    MemoryRepository<Event> repository = MemoryRepository<Event>();
    repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafdds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.remove(Event::getIdFromTitleAndDate("dfas", "/2022/10/23/10:24"));
    assert(repository.getAllEntities().size() == 3);
    try {
        repository.remove(Event("dfasdsaaa", "fdas", 3, "/2022/10/23/10:24",
                                "https://stackoverflow.com/questions/3385229").getId());
        assert(false);
    } catch (RepositoryException &repositoryException) {
        assert(true);
    }
}

void TestRepository::testUpdateRepository() {
    MemoryRepository<Event> repository = MemoryRepository<Event>();
    repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafdds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.update(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    assert(repository.getAllEntities().size() == 4);
    try {
        repository.update(
                Event("dfasdsaaa", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
        assert(false);
    } catch (RepositoryException &repositoryException) {
        assert(true);
    }
}

void TestRepository::testGetElementRepository() {
    MemoryRepository<Event> repository = MemoryRepository<Event>();
    repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafdds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    assert(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229")
           == repository.getElementById(Event::getIdFromTitleAndDate("fdsas", "/2022/10/23/10:24")));
    try {
        repository.getElementById(Event::getIdFromTitleAndDate("dfasdsaaa", "/2022/10/23/10:24"));
        assert(false);
    } catch (RepositoryException &repositoryException) {
        assert(true);
    }
}

void TestRepository::testIsElementPresentInRepository() {
    MemoryRepository<Event> repository = MemoryRepository<Event>();
    repository.add(Event("dfas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("fdsas", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    repository.add(Event("dfafdds", "fdas", 3, "/2022/10/23/10:24", "https://stackoverflow.com/questions/3385229"));
    assert(repository.isPresent(Event::getIdFromTitleAndDate("fdsas", "/2022/10/23/10:24")));
    assert(!repository.isPresent(Event::getIdFromTitleAndDate("fdfdasdfassas", "/2022/10/23/10:24")));
}

void TestRepository::testAllRepository() {
    TestRepository::testAddAndListElementsRepository();
    TestRepository::testRemoveRepository();
    TestRepository::testUpdateRepository();
    TestRepository::testGetElementRepository();
    TestRepository::testIsElementPresentInRepository();
}
