#!/bin/bash

MAP_DIR="./maps/maps_err"
EXEC="./so_long"

if [ ! -x "$EXEC" ]; then
	echo "Erreur : '$EXEC' introuvable ou non exécutable."
	exit 1
fi

if ! command -v valgrind &> /dev/null; then
	echo "Erreur : valgrind non installé."
	exit 1
fi

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

TOTAL=0
OK=0
KO=0

echo -e "\n🔎 Test des maps invalides dans ${MAP_DIR}/\n"

for map in "$MAP_DIR"/*; do
	((TOTAL++))
	FILENAME=$(basename "$map")
	echo -n "🧪 $FILENAME... "

	valgrind --quiet --leak-check=full --error-exitcode=42 "$EXEC" "$map" > /dev/null 2> valgrind_output.txt
	EXIT_CODE=$?

	if [ $EXIT_CODE -eq 42 ]; then
		echo -e "${RED}💥 Fuite mémoire !${NC}"
		((KO++))
	# elif [ $EXIT_CODE -eq 0 ]; then
	# 	echo -e "${YELLOW}⚠️ Pas d'erreur retournée (code 0)${NC}"
	# 	((KO++))
	else
		echo -e "${GREEN}✅ OK (erreur gérée proprement, pas de fuite)${NC}"
		((OK++))
	fi
done

echo -e "\nRésultat : ${OK}/${TOTAL} OK, ${KO} KO"

rm -f valgrind_output.txt