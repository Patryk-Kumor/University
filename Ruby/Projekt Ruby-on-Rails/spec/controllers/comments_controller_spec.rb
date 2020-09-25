require 'rails_helper'

RSpec.describe CommentsController, type: :controller do
  describe 'DELETE #destroy' do
    subject { delete :destroy, params: { id: comment.id } }
    let(:product) { create :product }
    let(:comment) { create :comment, product_id: product.id }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject).to redirect_to(root_path)
    end

    it do
      sign_in admin
      subject
      expect(controller.flash[:notice]).to eq('Comment was destroyed!')
    end
  end

  describe 'GET #report' do
    subject { get :report, params: { id: comment.id } }
    let(:product) { create :product }
    let(:comment) { create :comment, product_id: product.id }
    let(:user) { create :user }

    it do
      sign_in user
      expect(subject).to redirect_to(comment.product)
    end

    it do
      sign_in user
      subject
      expect(controller.flash[:notice]).to eq('Comment reported!')
    end
  end

  describe 'GET #undo_report' do
    subject { get :undo_report, params: { id: comment.id } }
    let(:product) { create :product }
    let(:comment) { create :comment, product_id: product.id }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject).to redirect_to(comments_reported_path)
    end

    it do
      sign_in admin
      subject
      expect(controller.flash[:notice]).to eq('Request rejected!')
    end
  end
end
