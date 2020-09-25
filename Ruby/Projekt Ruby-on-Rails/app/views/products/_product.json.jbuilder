json.extract! product, :id, :name, :price, :description, :category, :amount, :created_at, :updated_at
json.url product_url(product, format: :json)
