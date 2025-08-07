{% assign all_pages = site.pages | sort: "path" %}

<h1>所有文章</h1>

{% assign categories = "" | split: "," %}
{% assign valid_ext = "md,cpp" | split: "," %}

{% for page in all_pages %}
  {% assign dirs = page.path | split: "/" %}
  {% assign ext = dirs.last | split: "." | last | downcase %}

  {% if valid_ext contains ext and dirs.size > 1 %}
      {% assign category = dirs[0] %}
      {% unless categories contains category %}
        {% assign categories = categories | push: category %}
      {% endunless %}
  {% endif %}
{% endfor %}

{% for category in categories %}
  <h2>{{ category }}</h2>
  <ul>
    {% assign displayed_files = "" | split: "," %}

    {% for page in all_pages %}
      {% assign dirs = page.path | split: "/" %}
      {% assign ext = dirs.last | split: "." | last | downcase %}

      {% if page.path contains category and valid_ext contains ext %}
        {% assign title = page.path %}
        {% assign subpath = page.path %}

        {% assign linkpath = subpath %}

        {% if ext == "md" %}
          {% if dirs.last == "README.md" %}
            {% assign linkpath = subpath | replace: 'README.md', 'index.html' %}
          {% else %}
            {% assign linkpath = subpath | replace: '.md', '.html' %}
          {% endif %}
        {% endif %}

        {% unless displayed_files contains linkpath %}
          {% assign displayed_files = displayed_files | push: linkpath %}
          <li>
            <a href="{{ linkpath }}">{{ linkpath }}</a>
          </li>
        {% endunless %}
      {% endif %}
    {% endfor %}
  </ul>
{% endfor %}
