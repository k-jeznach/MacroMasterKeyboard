/******************************************************************************
 * File:        os.h
 * Author:      Konrad Jeznach
 * Email:       konznach@gmail.com
 * GitHub:      https://github.com/k-jeznach
 *
 * Copyright (c) 2025 Konrad Jeznach. All rights reserved.
 ******************************************************************************/

#ifndef OS_H
#define OS_H

#define OSPRIORITYNONE 0       ///< No priority (not initialized).
#define OSPRIORITYIDLE 1       ///< Reserved for Idle thread.
#define OSPRIORITYLOW 8        ///< Priority: low
#define OSPRIORITYLOW1 (8 + 1) ///< Priority: low + 1
#define OSPRIORITYLOW2 (8 + 2)
#define OSPRIORITYLOW3 (8 + 3)
#define OSPRIORITYLOW4 (8 + 4)
#define OSPRIORITYLOW5 (8 + 5)
#define OSPRIORITYLOW6 (8 + 6)
#define OSPRIORITYLOW7 (8 + 7)
#define OSPRIORITYBELOWNORMAL 16 ///< Priority: below normal
#define OSPRIORITYBELOWNORMAL1 (16 + 1)
#define OSPRIORITYBELOWNORMAL2 (16 + 2)
#define OSPRIORITYBELOWNORMAL3 (16 + 3)
#define OSPRIORITYBELOWNORMAL4 (16 + 4)
#define OSPRIORITYBELOWNORMAL5 (16 + 5)
#define OSPRIORITYBELOWNORMAL6 (16 + 6)
#define OSPRIORITYBELOWNORMAL7 (16 + 7)
#define OSPRIORITYNORMAL 24 ///< Priority: normal
#define OSPRIORITYNORMAL1 (24 + 1)
#define OSPRIORITYNORMAL2 (24 + 2)
#define OSPRIORITYNORMAL3 (24 + 3)
#define OSPRIORITYNORMAL4 (24 + 4)
#define OSPRIORITYNORMAL5 (24 + 5)
#define OSPRIORITYNORMAL6 (24 + 6)
#define OSPRIORITYNORMAL7 (24 + 7)
#define OSPRIORITYABOVENORMAL 32 ///< Priority: above normal
#define OSPRIORITYABOVENORMAL1 (32 + 1)
#define OSPRIORITYABOVENORMAL2 (32 + 2)
#define OSPRIORITYABOVENORMAL3 (32 + 3)
#define OSPRIORITYABOVENORMAL4 (32 + 4)
#define OSPRIORITYABOVENORMAL5 (32 + 5)
#define OSPRIORITYABOVENORMAL6 (32 + 6)
#define OSPRIORITYABOVENORMAL7 (32 + 7)
#define OSPRIORITYHIGH 40 ///< Priority: high
#define OSPRIORITYHIGH1 (40 + 1)
#define OSPRIORITYHIGH2 (40 + 2)
#define OSPRIORITYHIGH3 (40 + 3)
#define OSPRIORITYHIGH4 (40 + 4)
#define OSPRIORITYHIGH5 (40 + 5)
#define OSPRIORITYHIGH6 (40 + 6)
#define OSPRIORITYHIGH7 (40 + 7)
#define OSPRIORITYREALTIME 48 ///< Priority: realtime
#define OSPRIORITYREALTIME1 (48 + 1)
#define OSPRIORITYREALTIME2 (48 + 2)
#define OSPRIORITYREALTIME3 (48 + 3)
#define OSPRIORITYREALTIME4 (48 + 4)
#define OSPRIORITYREALTIME5 (48 + 5)
#define OSPRIORITYREALTIME6 (48 + 6)
#define OSPRIORITYREALTIME7 (48 + 7)
#define OSPRIORITYISR 56              ///< Reserved for ISR deferred thread.
#define OSPRIORITYERROR -1            ///< System cannot determine priority or illegal priority.
#define OSPRIORITYRESERVED 0x7FFFFFFF ///< Prevents enum down-size compiler optimization.

#endif