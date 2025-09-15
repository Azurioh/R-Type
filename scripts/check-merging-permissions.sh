# Check if origin branch is given
if [[ -z $1 ]]; then
    echo "You must provide the origin branch that you want to merge."
    exit 1
fi

# Check if destination branch is given
if [[ -z $2 ]]; then
    echo "You must provide the destination branch for the merge."
    exit 1
fi

# Staging branch protections
if [[ $2 == "staging" ]] -a [[ $1 != "main" ]]; then
    echo "You can't merge your branch to the staging branch."
    echo "Only PR from main branch are allowed."
    exit 1
fi

# Production branch protections
if [[ $2 == "production" ]] -a [[ $1 != "staging "]]; then
    echo "You can't merge your branch to the production branch."
    echo "Only PR from staging branch are allowed."
    exit 1
fi
