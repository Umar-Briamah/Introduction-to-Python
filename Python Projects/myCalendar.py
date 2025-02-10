from ics import Calendar, Event

# Step 1: Create a new calendar
cal = Calendar()

# Step 2: Create a new event
event1 = Event()
event1.name = "My Event"
event1.begin = '2025-02-10 10:00:00'
event1.end = '2025-02-10 12:00:00'
cal.events.add(event1)

# Step 3: Add another event
event2 = Event()
event2.name = "Another Event"
event2.begin = '2025-02-12 15:00:00'
event2.end = '2025-02-12 16:00:00'
cal.events.add(event2)

# Step 4: Save the calendar to a file
with open('my_calendar.ics', 'w') as my_file:
    my_file.writelines(cal)

# Step 5: Read the calendar back from the file
with open('my_calendar.ics', 'r') as my_file:
    calendar_from_file = Calendar(my_file.read())

# Step 6: Print all events in the calendar
for event in calendar_from_file.events:
    print(f"Event Name: {event.name}")
    print(f"Start: {event.begin}")
    print(f"End: {event.end}")
    print("---------")

# Step 7: Modify an existing event (for example, changing the name)
event_to_modify = next(event for event in calendar_from_file.events if event.name == "My Event")
event_to_modify.name = "Updated Event Name"

# Step 8: Save the updated calendar back to a file
with open('my_updated_calendar.ics', 'w') as my_file:
    my_file.writelines(calendar_from_file)
