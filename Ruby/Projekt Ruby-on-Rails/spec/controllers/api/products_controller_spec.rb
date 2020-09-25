require 'rails_helper'

RSpec.describe Api::ProductsController do
  describe 'GET #index' do
    subject { get :index, params: { key: key } }
    let(:key) { 'Test' }

    let!(:product) { create :product, name: 'Tester Product' }

    it do
      expect(subject).to be_successful
      expect(JSON.parse(subject.body))
        .to eq([{ 'id' => product.id, 'name' => product.name }])
    end
  end
end
