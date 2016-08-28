//
// Created by monty on 27/08/16.
//

#ifndef BLANKSLATE_CGAMESNAPSHOT_H
#define BLANKSLATE_CGAMESNAPSHOT_H

namespace odb {
    class CGameSnapshot {
    public:
        IntGameMap state;
	std::vector< std::pair<int, int>> visited;
    };
}

#endif //BLANKSLATE_CGAMESNAPSHOT_H
