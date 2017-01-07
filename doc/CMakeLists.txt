ADD_CUSTOM_TARGET("docs")
ADD_CUSTOM_COMMAND(TARGET "docs"
		COMMAND dia -e schema.png -t png schema.dia
		COMMAND pandoc -f markdown -t latex -o tsdss.pdf tsdss.md
		COMMAND pandoc -f markdown -t latex -o tsdss-user-guide.pdf
				tsdss-user-guide.md)
